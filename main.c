#include "client.h"
#include "socket.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <sys/socket.h>
#include <arpa/inet.h>



int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        perror("Usage: ./server <password>");
        return 1;
    }

    if (strcmp(argv[1], "123") != 0)
    {
        perror("Wrong password");
        return 0;
    }

    int client_fd;
    int server_fd = create_server_socket();


    struct sockaddr_in client_addr;

    socklen_t client_len = sizeof(client_addr);

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

        int *fd_ptr = malloc(sizeof(int));

        if (!fd_ptr)
        {
            close(client_fd);
            continue;
        }

        *fd_ptr = client_fd;
        
        pthread_t tid;

        if (pthread_create(&tid,
                           NULL,
                           client_handler,
                           fd_ptr
                            ) != 0)
        {
            perror("thread creation!");
            free(fd_ptr);
            close(client_fd);
            continue;
        }

        pthread_detach(tid);
    }

    close(server_fd);
    return 0;
}
