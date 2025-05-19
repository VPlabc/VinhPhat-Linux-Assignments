#ifndef Main_H
#define Main_H
#include "CLI.h"

void cleanup(PeerState *state);
void set_nonblocking(int sock);

#endif // Main_H