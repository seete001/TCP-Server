CC = gcc

CFLAGS = -Wall -Wextra -Wpedantic -pthread -Iinclude

SRC = src/main.c \
      src/auth.c \
      src/client.c \
      src/socket.c \
      src/serverpass.c

OBJ = $(SRC:src/%.c=obj/%.o)

TARGET = bin/server

$(TARGET): $(OBJ)
	mkdir -p bin
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

obj/%.o: src/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) 123

clean:
	rm -rf obj bin

.PHONY: clean run
