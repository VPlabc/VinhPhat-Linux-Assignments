#include "../inc/CLI.h"

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
