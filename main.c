#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define PASSBUFF 64
#define MAX_ATTEMPTS 3

// Authenticate client
int validate(int client_fd)
{
    const char *req_pass = "Password: ";

    if (send(client_fd, req_pass, strlen(req_pass), 0) < 0)
    {
        perror("send");
        return 1;
    }

    char pass_buffer[PASSBUFF];

    ssize_t password_bytes =
        recv(client_fd, pass_buffer, PASSBUFF - 1, 0);

    if (password_bytes <= 0)
        return 1;

    pass_buffer[password_bytes] = '\0';

    // Remove trailing newline(s)
    pass_buffer[strcspn(pass_buffer, "\r\n")] = '\0';

    if (strcmp(pass_buffer, "admin") != 0)
    {
        const char *msg = "Invalid password.\n";
        send(client_fd, msg, strlen(msg), 0);
        return 1;
    }

    const char *msg = "Authentication successful.\n";
    send(client_fd, msg, strlen(msg), 0);

    return 0;
}

int main(void)
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
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Allow quick restart of server
    int opt = 1;
    if (setsockopt(server_fd,
                   SOL_SOCKET,
                   SO_REUSEADDR,
                   &opt,
                   sizeof(opt)) < 0)
    {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Configure address
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd,
             (struct sockaddr *)&server_addr,
             sizeof(server_addr)) < 0)
    {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen
    if (listen(server_fd, 5) < 0)
    {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    while (1)
    {
        client_fd = accept(server_fd,
                           (struct sockaddr *)&client_addr,
                           &client_len);

        if (client_fd < 0)
        {
            perror("accept");
            continue;
        }

        printf("Incoming connection from %s\n",
               inet_ntoa(client_addr.sin_addr));

        int authenticated = 0;

        for (int attempts = 0; attempts < MAX_ATTEMPTS; attempts++)
        {
            if (validate(client_fd) == 0)
            {
                authenticated = 1;
                break;
            }
        }

        if (!authenticated)
        {
            printf("Authentication failed.\n");
            close(client_fd);
            continue;
        }

        printf("Client authenticated.\n");

        while (1)
        {
            ssize_t bytes_received =
                recv(client_fd,
                     buffer,
                     BUFFER_SIZE - 1,
                     0);

            if (bytes_received <= 0)
                break;

            buffer[bytes_received] = '\0';

            buffer[strcspn(buffer, "\r\n")] = '\0';

            if (strcmp(buffer, "quit") == 0)
            {
                printf("Client requested disconnect.\n");
                break;
            }

            printf("Received: %s\n", buffer);

            if (send(client_fd,
                     buffer,
                     strlen(buffer),
                     0) < 0)
            {
                perror("send");
                break;
            }
        }

        printf("Client disconnected.\n");
        close(client_fd);
    }

    close(server_fd);
    return 0;
}
