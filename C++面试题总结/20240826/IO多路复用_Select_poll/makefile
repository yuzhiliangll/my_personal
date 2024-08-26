CC = cc
CFLAGS = -g

all: client server

client: select_client.o
	$(CC) $(CFLAGS) -o client select_client.o

server: select_server.o
	$(CC) $(CFLAGS) -o server select_server.o

select_client.o: select_client.c
	$(CC) $(CFLAGS) -c select_client.c

select_server.o: select_server.c
	$(CC) $(CFLAGS) -c select_server.c

clean:
	rm -f *.o client server