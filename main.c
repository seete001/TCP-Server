// Server

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 4096

int main()
{
    int server_fd;
    int client_fd;

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    socklen_t client_len = sizeof(client_addr);
    
    char buffer[BUFFER_SIZE];

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0)
    {
        perror("Failed to make a socket");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket to the PORT
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Failed to bind the socket");
        exit(EXIT_FAILURE);
        close(server_fd);
    }

    // Start listening
    if (listen(server_fd, 5) < 0)
    {
        perror("Failed to listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    printf("Server listening on port 8080 ...\n");

    while (1)
    {
        client_fd = accept(server_fd, 
                          (struct sockaddr*)&client_addr,
                          &client_len);
        if (client_fd < 0)
        {
            perror("Failed to accept");
            continue;
        }
        printf("Client connected\n");
        
        while (1)
        {
            // Recieve data
            ssize_t bytes_recieved = 
                                recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
            if (bytes_recieved <= 0) break;

            buffer[bytes_recieved] = '\0';

            if (strcmp(buffer, "quit\n") == 0)
            {
                printf("User requested fin");
                break;
            }

            printf("Recieved: %s\n", buffer);
            
            send(client_fd, buffer, bytes_recieved, 0);
        }
        printf("Client disconnected\n");

        close(client_fd);
    }
    return 0;
}
