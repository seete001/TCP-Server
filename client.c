#include "client.h"
#include "auth.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

#define BUFFER_SIZE 4096
#define MAX_ATTEMPTS 3

void *client_handler(void *arg)
{
    int client_fd = *(int *)arg;
    free(arg);

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
        return NULL;
    }

    printf("Client authenticated.\n");
    
    char buffer[BUFFER_SIZE];
    while (1)
    {
        ssize_t bytes_received =
        recv(client_fd,
             buffer,
             BUFFER_SIZE - 1,
             0);

        if (bytes_received <= 0) break;

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
                 bytes_received,
                 0) < 0)
        {
            perror("send");
            break;
        }
    }

    printf("Client disconnected.\n");
        
    close(client_fd);

    return NULL;
}
