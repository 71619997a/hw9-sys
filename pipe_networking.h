#ifndef PIPE_NETWORKING_H
#define PIPE_NETWORKING_H
#define MESSAGE_BUFFER_SIZE 64
#define HANDSHAKE_BUFFER_SIZE 64
#define WKP "pipe"
int server_handshake(int *);
int server_handshake1(char *);
int server_handshake2(char *, int);
int client_handshake(int *);
#endif
