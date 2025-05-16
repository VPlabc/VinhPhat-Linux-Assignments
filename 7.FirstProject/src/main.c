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

void cleanup(PeerState *state);
void set_nonblocking(int sock);

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

void print_help() {
    printf("=============================================\n");
    printf("</>              Commands list               \n\n");
    printf("🛟  help - Show this help\n");
    printf("🔎 myip - Show my IP address\n");
    printf("🔎 myport - Show my port\n");
    printf("🔗 connect <ip> <port> - Connect to a peer\n");
    printf("📜 list - List all connections\n");
    printf("🔨 terminate <id> - Terminate a connection\n");
    printf("🚀 send <id> <message> - Send a message\n");
    printf("❌ exit - Exit the program\n");
    printf("=============================================\n");
}

void get_myip() {
    struct ifaddrs *addrs, *tmp;
    getifaddrs(&addrs);
    for (tmp = addrs; tmp != NULL; tmp = tmp->ifa_next) {
        if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET) {
            struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp->ifa_addr;
            if (strcmp(tmp->ifa_name, "lo") != 0) {
                printf("🔎 IP: %s\n", inet_ntoa(pAddr->sin_addr));
            }
        }
    }
    freeifaddrs(addrs);
}

void handle_disconnection(PeerState *state, Connection *conn, const char *reason) {
    printf("❌ Connection ID %d (%s:%d) closed: %s\n", conn->id, conn->ip, conn->port, reason);

    // Đóng socket và xóa kết nối khỏi danh sách
    close(conn->socket);

    // Xóa kết nối khỏi danh sách liên kết
    Connection *prev = NULL;
    Connection *current = state->connections;
    while (current != NULL) {
        if (current == conn) {
            if (prev) {
                prev->next = current->next;
            } else {
                state->connections = current->next;
            }
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
}

void handle_exit(PeerState *state) {
    printf("❌ Exiting program...\n");
    cleanup(state);
    exit(0);
}

void handle_command(PeerState *state, char *command) {
    // Command parsing and handling logic here
    if (strncmp(command, "help", 4) == 0) {
        print_help();
    } else if (strncmp(command, "myip", 4) == 0) {
        get_myip();
    } else if (strncmp(command, "myport", 6) == 0) {
        printf("🔎 My port: %d\n", state->listen_port);
    } else if (strncmp(command, "connect", 7) == 0) {
        char ip[INET_ADDRSTRLEN];
        int port;
        struct sockaddr_in addr;

        if (sscanf(command + 8, "%s %d", ip, &port) == 2) {
            int sock = socket(AF_INET, SOCK_STREAM, 0);

            if (sock < 0) {
                perror("socket");
                return;
            }

            memset(&addr, 0, sizeof(addr));
            addr.sin_family = AF_INET;
            inet_pton(AF_INET, ip, &addr.sin_addr);
            addr.sin_port = htons(port);

            if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
                perror("connect");
                close(sock);
                return;
            }

            add_connection(state, sock, ip, port);
            printf("\n ✅ Connected successfully. ready for transmission\n");

        } else {
            printf("\n ⚠️   Usage: connect <ip> <port>\n");
        }

    } else if (strncmp(command, "list", 4) == 0) {
        Connection *sorted_connections = NULL;
        Connection *current = state->connections;
        
        // Sort connections by ID
        while (current != NULL) {
            Connection *new_conn = malloc(sizeof(Connection));
            *new_conn = *current;
            new_conn->next = NULL;

            if (sorted_connections == NULL || new_conn->id < sorted_connections->id) {
                new_conn->next = sorted_connections;
                sorted_connections = new_conn;
            } else {
                Connection *sorted_current = sorted_connections;
                while (sorted_current->next != NULL && sorted_current->next->id < new_conn->id) {
                    sorted_current = sorted_current->next;
                }
                new_conn->next = sorted_current->next;
                sorted_current->next = new_conn;
            }
            current = current->next;
        }

        printf("\n===================================\n");
        printf("📜          Peer list               \n");
        printf(" ID |      IP address    | Port.no\n");
        for (Connection *conn = sorted_connections; conn != NULL; conn = conn->next) {
            printf(" %d  |   %s  | %d\n", conn->id, conn->ip, conn->port);
        }
        printf("====================================\n\n");
        
    } else if (strncmp(command, "terminate", 9) == 0) {
        int id;
        if (sscanf(command + 10, "%d", &id) == 1) {
            Connection *prev = NULL;
            Connection *conn = state->connections;

            while (conn != NULL && conn->id != id) {
                prev = conn;
                conn = conn->next;
            }

            if (conn != NULL) {
                close(conn->socket);
                if (prev) prev->next = conn->next;
                else state->connections = conn->next;
                free(conn);
                printf("✅ Terminated connection ID: %d\n", id);
                conn = NULL; // Prevent further access to the freed connection
            } else {
                printf("❌ No connection found with ID: %d\n", id);
            }

        } else {
            printf("⚠️ Usage: terminate <id>\n");
        }
    } else if (strncmp(command, "send", 4) == 0) {
        int id;
        char message[BUFFER_SIZE];
        if (sscanf(command + 5, "%d %[^\n]", &id, message) == 2) {
            Connection *conn = state->connections;

            while (conn != NULL && conn->id != id) {
                conn = conn->next;
            }
            if (conn != NULL) {
                send(conn->socket, message, strlen(message), 0);
                printf("== 🚀 == Sent message to ID: %d =====\n", id );
                printf("%s", message);
                printf("\n=================================\n");
            } else {
                printf("❌ No connection found with ID: %d\n", id);
            }

        } else {
            printf("⚠️ Usage: send <id> <message>\n");
        }

    } else if (strncmp(command, "exit", 4) == 0) {
        handle_exit(state);
    } else {
        printf("⚠️ Unknown command: %s", command);
    }
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