#ifndef PIPE_NETWORKING_H
#define PIPE_NETWORKING_H
#define MESSAGE_BUFFER_SIZE 64
#define WKP "pipe"
int server_handshake(int *);
int client_handshake(int *);
#endif
