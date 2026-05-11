# TCP Server in C

A simple TCP echo server written from scratch in C using POSIX sockets.

## Features

- TCP socket server
- Accepts client connections
- Receives messages from clients
- Echoes messages back
- Handles client disconnects
- Simple `quit` command support

---

## Build

Compile with GCC:

```bash
gcc main.c -o server
```

---

## Run

Start the server:

```bash
./server
```

The server listens on:

```text
localhost:8080
```

---

## Test with Netcat

Open another terminal and connect:

```bash
nc localhost 8080
```

Send messages:

```text
hello
testing
quit
```

---

## Concepts Used

- `socket()`
- `bind()`
- `listen()`
- `accept()`
- `recv()`
- `send()`
- TCP/IP networking
- Blocking I/O

---

## Future Improvements

- Multi-client support
- Non-blocking sockets
- `select()` / `poll()` / `epoll`
- Basic HTTP server
- Thread pool
- Better error handling

---

## Learning Goal

This project was built to understand low-level networking and how TCP servers work internally without external libraries.
