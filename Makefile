CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -pthread

server : main.o auth.o client.o
	$(CC) $(CFLAGS) main.o auth.o client.o -o server

main.o : main.c
	$(CC) $(CFLAGS) -c main.c

auht.o : auth.c auth.h
	$(CC) $(CFLAGS) -c auth.c

client.o : client.c client.h auth.h
	$(CC) $(CFLAGS) -c client.c

clean:
	rm -f *.o server
