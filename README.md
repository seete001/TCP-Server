# TCP Echo Server in C

A multithreaded TCP echo server written in C using POSIX sockets and POSIX threads. This project was built as a learning exercise to explore low-level networking, TCP communication, authentication, concurrency, and systems programming without relying on external networking frameworks.

---

## Features

* TCP socket server
* Accepts multiple client connections simultaneously
* Thread-per-client architecture using POSIX threads
* Password-based authentication
* Echoes received messages back to the sender
* Graceful client disconnect handling
* Simple `quit` command support
* Socket reuse support (`SO_REUSEADDR`)
* Modular project structure
* Automated builds using Make
* Separated source, header, object, and binary directories

---

## Project Structure

```text
project/
├── Makefile
├── README.md
├── bin/
│   └── server
├── include/
│   ├── auth.h
│   ├── client.h
│   ├── serverpass.h
│   └── socket.h
├── obj/
│   ├── auth.o
│   ├── client.o
│   ├── main.o
│   ├── serverpass.o
│   └── socket.o
└── src/
    ├── auth.c
    ├── client.c
    ├── main.c
    ├── serverpass.c
    └── socket.c
```

---

## File Overview

| File                   | Purpose                                                         |
| ---------------------- | --------------------------------------------------------------- |
| `src/main.c`           | Program entry point, server startup, connection acceptance loop |
| `src/socket.c`         | Socket creation, binding, listening, and server setup           |
| `include/socket.h`     | Socket-related declarations                                     |
| `src/client.c`         | Client thread handling and message processing                   |
| `include/client.h`     | Client handler declarations                                     |
| `src/auth.c`           | Authentication logic                                            |
| `include/auth.h`       | Authentication declarations                                     |
| `src/serverpass.c`     | Server password validation                                      |
| `include/serverpass.h` | Password validation declarations                                |
| `obj/*.o`              | Intermediate object files generated during compilation          |
| `bin/server`           | Compiled executable                                             |
| `Makefile`             | Build automation                                                |

---

## Build

Compile the project:

```bash
make
```

This creates:

```text
obj/
bin/server
```

Clean generated files:

```bash
make clean
```

---

## Run

Start the server:

```bash
make run
```

or directly:

```bash
./bin/server 123
```

The server listens on:

```text
0.0.0.0:8080
```

---

## Design Notes

The project follows a modular design:

* Networking code is isolated in `socket.c`
* Authentication logic is isolated in `auth.c`
* Password validation is isolated in `serverpass.c`
* Client handling is isolated in `client.c`
* `main.c` remains focused on accepting incoming connections and spawning worker threads

This separation makes the codebase easier to maintain and extend as new features are added.

---

## Concepts Practiced

### Networking

* POSIX Sockets
* TCP/IP Networking
* Client-Server Architecture
* Blocking I/O

### Concurrency

* POSIX Threads (`pthread`)
* Detached Threads
* Thread-per-Client Design

### Systems Programming

* Dynamic Memory Allocation
* Resource Management
* Signal Handling Fundamentals
* Modular Program Architecture
* Build Automation with Make
* Header and Source File Organization

---

## Future Improvements

* Password hashing
* User account system
* Configuration file support
* Graceful SIGINT shutdown handling
* Thread pool implementation
* Server-side logging
* TLS/SSL encryption
* Non-blocking sockets
* `select()`, `poll()`, or `epoll()`
* Chat server functionality
* Broadcast messaging
* Private messaging
* Administrative commands

```
```

