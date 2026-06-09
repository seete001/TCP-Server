objects = main.o auth.o client.o socket.o serverpass.o
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -pthread

server : $(objects)
	$(CC) $(CFLAGS) $(objects) -o server

main.o : main.c
	$(CC) $(CFLAGS) -c main.c

auth.o : auth.c auth.h
	$(CC) $(CFLAGS) -c auth.c

client.o : client.c client.h auth.h
	$(CC) $(CFLAGS) -c client.c

socket.o : socket.c socket.h
	$(CC) $(CFLAGS) -c socket.c

serverpass.o : serverpass.c serverpass.h
	$(CC) $(CFLAGS) -c serverpass.c
	
run : server
	./server 123

clean:
	rm -f *.o server
