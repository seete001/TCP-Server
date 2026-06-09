# TCP Chat Server in C

A multithreaded TCP server written in C using POSIX sockets and POSIX threads.  
This project started as a learning exercise for low-level networking and has evolved into a modular foundation for a real-time chat server.

It demonstrates TCP networking, concurrency, modular C architecture, and build system design using Make.

---

## Features

- TCP socket server
- Accepts multiple client connections simultaneously
- Thread-per-client architecture using POSIX threads
- Password-based authentication
- Basic command handling (`time`, `help`, `quit`)
- Echo-style message handling (legacy behavior)
- Socket reuse support (`SO_REUSEADDR`)
- Graceful client disconnect handling
- Modular project structure (separated networking, auth, and client logic)
- Build automation using Make
- Organized source, header, object, and binary directories

---

## Project Structure

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

---

## File Overview

- src/main.c → Server entry point, accept loop, thread creation  
- src/socket.c → TCP socket creation, bind, listen setup  
- include/socket.h → Socket function declarations  
- src/client.c → Client thread handling and command processing  
- include/client.h → Client handler declarations  
- src/auth.c → Authentication logic  
- include/auth.h → Authentication declarations  
- src/serverpass.c → Server password validation  
- include/serverpass.h → Password handling declarations  
- obj/*.o → Compiled object files  
- bin/server → Final executable  
- Makefile → Build system  

---

## Build

make

This compiles all source files into obj/ and links them into:

bin/server

---

## Clean

make clean

---

## Run

make run

or:

./bin/server 123

---

## Client Connection

nc localhost 8080

---

## Commands

help
- show available commands
- time
- display server time
- quit
- disconnect from server

time output:
Current time: 2026-06-09 21:45:12

quit closes the connection.

---

## Design Overview

Networking Layer (socket.c)
- Socket creation
- Bind/listen setup

Client Layer (client.c)
- Handles each client thread
- Processes commands

Authentication Layer (auth.c, serverpass.c)
- Password validation

Main (main.c)
- Accept loop
- Thread creation

---

## Concepts Used

Networking:
- TCP sockets
- POSIX APIs

Concurrency:
- pthreads
- Thread-per-client model

Systems Programming:
- malloc/free
- snprintf
- Modular architecture
- Makefile builds

---

## Limitations

- No broadcasting (not a real chat yet)
- No usernames
- No encryption
- Thread-per-client scaling limits
- Password passed via CLI

---

## Roadmap

- Broadcast chat system
- Usernames
- Private messages (/msg)
- /users command
- Mutex-protected client list
- Thread pool or select/poll/epoll
- TLS encryption
- Logging system
- Graceful shutdown

---

## License

Educational use only.
