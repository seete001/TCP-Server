# TCP Server in C

A simple TCP echo server written from scratch in C using POSIX sockets. This project was built as a learning exercise to understand low-level networking, TCP communication, client-server architecture, and socket programming without relying on external libraries.

## Features

* TCP socket server
* Accepts client connections
* Password-based client authentication
* Limited authentication attempts
* Receives messages from clients
* Echoes messages back to the sender
* Handles client disconnects gracefully
* Simple `quit` command support
* Input validation for authentication
* Socket reuse support (`SO_REUSEADDR`)

---

## Recent Changes

The server has been updated with several improvements:

* Added password authentication before allowing access.
* Added authentication retry limits to prevent infinite login loops.
* Improved handling of client disconnections.
* Added newline (`\n` / `\r\n`) sanitization for password validation.
* Added socket reuse support using `SO_REUSEADDR`.
* Improved error handling for `send()` and `recv()` operations.
* Added client connection logging.

---

## Authentication

When a client connects, the server prompts for a password:

```text
Password:
```

The default password is:

```text
admin
```

Clients must authenticate successfully before being allowed to send messages.

---

## Build

Compile with GCC:

```bash
gcc main.c -o server
```

For additional warnings:

```bash
gcc -Wall -Wextra -pedantic main.c -o server
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

Example session:

```text
Password: admin
Authentication successful.

hello
hello

testing
testing

quit
```

---

## Concepts Used

* POSIX Sockets
* TCP/IP Networking
* Client-Server Architecture
* `socket()`
* `bind()`
* `listen()`
* `accept()`
* `recv()`
* `send()`
* `setsockopt()`
* Blocking I/O
* Input Validation
* Basic Authentication

---

## Project Structure

```text
project/
├── main.c
└── README.md
```

---

## Current Limitations

* Single-client handling (one connection processed at a time)
* Plain-text password authentication
* No encryption (communication is not secure)
* No user management system
* No logging to files
* No configuration file support

---

## Future Improvements

* Multi-client support using threads
* Non-blocking sockets
* `select()`, `poll()`, or `epoll()`
* Configuration file support
* Password hashing
* TLS/SSL encryption
* User accounts and permissions
* Server-side logging
* Basic HTTP server implementation

---

## Learning Goals

This project was created to practice:

* Network programming in C
* TCP socket communication
* Authentication workflows
* Client-server interaction
* Error handling
* Resource management
* Systems programming fundamentals

---

## License

This project is provided for educational purposes and learning.

