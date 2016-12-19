#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "pipe_networking.h"

int server_handshake(int *readfrom) {
    printf("Creating WKP & waiting for connection\n");
    mkfifo(WKP, 0644);
    *readfrom = open(WKP, O_RDONLY);
    printf("Connection made\n");
    char client_message[MESSAGE_BUFFER_SIZE];
    read(*readfrom, client_message, MESSAGE_BUFFER_SIZE);
    printf("Received client FIFO: %s\n", client_message);
    unlink(WKP);
    int writeto = open(client_message, O_WRONLY);
    printf("Opened client FIFO\n");
    write(writeto, "I ARE SERVER", MESSAGE_BUFFER_SIZE);
    printf("Wrote message\n");
    read(*readfrom, client_message, MESSAGE_BUFFER_SIZE);
    printf("Got message from client: %s\n", client_message);
    printf("Server handshake complete\n");
    return writeto;
}

int server_handshake1(char *buf) {  // part 1 gets private FIFO thru WKP
    printf("Creating WKP & waiting for connection\n");
    mkfifo(WKP, 0644);
    int readfrom = open(WKP, O_RDONLY);
    printf("Connection made\n");
    read(readfrom, buf, HANDSHAKE_BUFFER_SIZE);
    printf("Received client FIFO: %s\n", buf);
    unlink(WKP);
    return readfrom;
}

int server_handshake2(char *buf, int readfrom) {  // part 2 works with private FIFO
    int writeto = open(buf, O_WRONLY);
    printf("Opened client FIFO\n");
    write(writeto, "I ARE SERVER", HANDSHAKE_BUFFER_SIZE);
    printf("Wrote message\n");
    read(readfrom, buf, HANDSHAKE_BUFFER_SIZE);  // we can overwrite buf b/c not used again
    printf("Got message from client: %s\n", buf);
    printf("Server handshake complete\n");
    return writeto;
}
    

int client_handshake(int *writeto) {
    setbuf(stdout, NULL);
    char fifoname[MESSAGE_BUFFER_SIZE];
    sprintf(fifoname, "secret%d", getpid());
    printf("Creating private FIFO %s", fifoname);
    mkfifo(fifoname, 0644);
    *writeto = open(WKP, O_WRONLY);
    printf("Connected to WKP\n");
    write(*writeto, fifoname, MESSAGE_BUFFER_SIZE);
    printf("Sent FIFO\n");
    int readfrom = open(fifoname, O_RDONLY);
    printf("Opened my private fifo\n");
    char server_message[MESSAGE_BUFFER_SIZE];
    read(readfrom, server_message, MESSAGE_BUFFER_SIZE);
    printf("Got message: %s\n", server_message);
    write(*writeto, "I BE CLIENT", MESSAGE_BUFFER_SIZE);
    printf("Wrote to server\n");
    printf("Client handshake complete\n");
    return readfrom;
}

