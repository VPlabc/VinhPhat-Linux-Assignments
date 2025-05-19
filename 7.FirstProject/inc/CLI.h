#ifndef CLI_H
#define CLI_H

void print_help();
void get_myip()
void handle_disconnection(PeerState *state, Connection *conn, const char *reason)
void handle_exit(PeerState *state);
void handle_command(PeerState *state, char *command);


#endif// CLI_H