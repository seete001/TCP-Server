
# TCP Echo Server in C

A multithreaded TCP echo server written in C using POSIX sockets and POSIX threads. This project was built as a learning exercise to explore low-level networking, TCP communication, authentication, concurrency, and systems programming without relying on external networking frameworks.

---

## Features

* TCP socket server
* Accepts multiple client connections simultaneously
* Thread-per-client architecture using POSIX threads
* Password-based client authentication
* Configurable authentication attempt limit
* Echoes received messages back to the sender
* Graceful client disconnect handling
* Simple `quit` command support
* Input sanitization for authentication
* Socket reuse support (`SO_REUSEADDR`)
* Modular project structure using multiple source and header files
* Build automation with Make

---

## Authentication

When a client connects, the server prompts for a password:

```text
Password:
```

Default password:

```text
admin
```

Clients must authenticate successfully before they can interact with the server.

After exceeding the maximum number of authentication attempts, the connection is closed.

---

## Project Structure

```text
project/
├── main.c
├── auth.c
├── auth.h
├── client.c
├── client.h
├── server.h
├── Makefile
└── README.md
```

### File Overview

| File       | Purpose                                              |
| ---------- | ---------------------------------------------------- |
| `main.c`   | Server setup, socket creation, connection acceptance |
| `auth.c`   | Client authentication logic                          |
| `auth.h`   | Authentication function declarations                 |
| `client.c` | Client thread handling and message processing        |
| `client.h` | Client handler declarations                          |
| `server.h` | Shared constants and definitions                     |
| `Makefile` | Build automation                                     |

---

## Build

Build the project using Make:

```bash
make
```

This compiles all source files and creates:

```text
server
```

Clean build artifacts:

```bash
make clean
```

---

## Run

Start the server:

```bash
./server
```

The server listens on:

```text
0.0.0.0:8080
```

which allows connections on all available network interfaces.

---

## Connecting to the Server

### Using Netcat

Open another terminal:

```bash
nc localhost 8080
```

### Example Session

```text
Password: admin
Authentication successful.

hello
hello

testing
testing

quit
```

The `quit` command closes the connection.

---

## Example: Multiple Clients

The server supports multiple simultaneous clients.

Terminal 1:

```bash
nc localhost 8080
```

Terminal 2:

```bash
nc localhost 8080
```

Each client is handled independently in its own thread.

---

## Concepts Used

### Networking

* POSIX Sockets
* TCP/IP Networking
* Client-Server Architecture
* Blocking I/O

### Socket Functions

* `socket()`
* `bind()`
* `listen()`
* `accept()`
* `recv()`
* `send()`
* `setsockopt()`

### Concurrency

* POSIX Threads (`pthread`)
* Thread Creation
* Detached Threads
* Concurrent Client Handling

### Systems Programming

* Dynamic Memory Allocation
* Resource Management
* Error Handling
* Modular Code Organization
* Build Automation with Make

---

## Current Limitations

* Password stored in source code
* Plain-text authentication
* No encryption (TLS/SSL)
* No user accounts
* No persistent storage
* No logging to files
* No thread pool implementation
* Uses blocking sockets

---

## Future Improvements

* Password hashing
* User account system
* Configuration file support
* Thread pool implementation
* Server-side logging
* TLS/SSL encryption
* Non-blocking sockets
* `select()`, `poll()`, or `epoll()`
* Chat server functionality
* Broadcast messaging
* Private messaging between clients
* Administrative commands

---

## Learning Goals

This project was created to practice:

* Network programming in C
* TCP communication
* Client authentication workflows
* Multithreaded programming
* POSIX threads
* Socket programming
* Error handling
* Resource management
* Modular software design
* Systems programming fundamentals

---

## License

This project is provided for educational and learning purposes.
