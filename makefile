all: server client fserver

fserver: pipe_networking.c fserver.c
	gcc -o fserver.out pipe_networking.c fserver.c

server: pipe_networking.c server.c
	gcc -o server.out pipe_networking.c server.c

client: pipe_networking.c client.c
	gcc -o client.out pipe_networking.c client.c

clean:
	-rm *.out
