#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

#include "../inc/main.h"

#define MAX_CONNECTIONS 10
#define BUFFER_SIZE 1024

typedef struct connection {
    int id;
    int socket;
    char ip[INET_ADDRSTRLEN];
    int port;
    char send_buffer[BUFFER_SIZE];
    int bytes_to_send;
    struct connection *next;
} Connection;

typedef struct {
    int listen_socket;
    int listen_port;
    Connection *connections;
    int next_connection_id;
} PeerState;


Connection *add_connection(PeerState *state, int socket, const char *ip, int port) {
    Connection *conn = malloc(sizeof(Connection));
    conn->id = state->next_connection_id++;
    conn->socket = socket;
    strncpy(conn->ip, ip, INET_ADDRSTRLEN);
    conn->port = port;
    conn->next = state->connections;
    state->connections = conn;
    set_nonblocking(conn->socket);
    return conn;
}

void cleanup(PeerState *state) {
    close(state->listen_socket);
    Connection *conn = state->connections;
    while (conn != NULL) {
        Connection *next = conn->next;
        shutdown(conn->socket, SHUT_RDWR);
        close(conn->socket);
        free(conn);
        conn = next;
    }
}

void set_nonblocking(int sock) {
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);
}

int get_socket_error(int sock) {
    int error = 0;
    socklen_t len = sizeof(error);
    getsockopt(sock, SOL_SOCKET, SO_ERROR, &error, &len);
    return error;
}

void async_send(Connection *conn, const char *message) {
    strncpy(conn->send_buffer, message, BUFFER_SIZE);
    conn->bytes_to_send = strlen(message);
}

int setup_listen_socket(int *port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return -1;

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(*port);

    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        close(sock);
        return -1;
    }

    socklen_t len = sizeof(addr);
    getsockname(sock, (struct sockaddr *)&addr, &len);
    // *port = ntohs(addr.sin_port);

    listen(sock, 5);
    return sock;
}

void main(int argc, char *argv[]) {
    
    if (argc != 2) {
        fprintf(stderr, "⚠️   Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    PeerState state;

    state.listen_port = (atoi(argv[1]));
    if (state.listen_port <= 0 || state.listen_port > 65535) {
        fprintf(stderr, "❌ Invalid port number. Please provide a port between 1 and 65535.\n");
        exit(1);
    }

    signal(SIGPIPE, SIG_IGN);

    state.connections = NULL;
    state.next_connection_id = 1;

    // Setup listening socket
    state.listen_socket = setup_listen_socket(&state.listen_port);
    if (state.listen_socket < 0) {
        perror("❌ Failed to setup listening socket");
        exit(1);
    }

    print_help();

    printf("\n✅  Application is listening on port %d\n", state.listen_port);

    // Main loop using select()
    fd_set read_fds;
    fd_set write_fds;
    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(state.listen_socket, &read_fds);

        // Add all connections to fd_set
        for (Connection *conn = state.connections; conn != NULL; conn = conn->next) {
            FD_SET(conn->socket, &read_fds);
        }

        if (select(FD_SETSIZE, &read_fds, NULL, NULL, NULL) < 0) {
            perror("❌ select error");
            continue;
        }

        // Handle input
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            char buffer[BUFFER_SIZE];
            if (fgets(buffer, BUFFER_SIZE, stdin)) {
                handle_command(&state, buffer);
            }
        }

        // Handle new connections
        if (FD_ISSET(state.listen_socket, &read_fds)) {
            struct sockaddr_in addr;
            socklen_t len = sizeof(addr);
            int new_sock = accept(state.listen_socket, (struct sockaddr *)&addr, &len);
            if (new_sock >= 0) {
                char ip[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &addr.sin_addr, ip, INET_ADDRSTRLEN);
                add_connection(&state, new_sock, ip, htons(addr.sin_port));
                printf("\n ✅ Accepted a new connection from address %s - port %d\n", ip, addr.sin_port);
            }
        }

        // Handle existing connections
        Connection *prev = NULL;
        Connection *conn = state.connections;
        while (conn != NULL) {
            if (FD_ISSET(conn->socket, &read_fds)) {
                char buffer[BUFFER_SIZE];
                int bytes = recv(conn->socket, buffer, BUFFER_SIZE, 0);
                if (bytes <= 0) {  
                    int error = get_socket_error(conn->socket);
                    if (error != 0) {
                        handle_disconnection(&state, conn, "Network error");
                    }
                    printf("❌ Connection ID %d (%s:%d) disconnected\n", conn->id, conn->ip, conn->port);
                    // Connection closed
                    Connection *next = conn->next; 
                    close(conn->socket);
                    if (prev) prev->next = next;
                    else state.connections = next;
                    free(conn);
                    conn = next;
                    continue;
                } else {
                    buffer[bytes] = '\0';
                    printf("\n== 📨 == message from %s - port: %d =====\n", conn->ip, conn->port);
                    printf("%s", buffer);
                    printf("\n======================================================\n");
                }
            }
            prev = conn;
            conn = conn->next;
        }
    }
}