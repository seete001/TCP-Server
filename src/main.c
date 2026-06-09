#include "client.h"
#include "socket.h"
#include "serverpass.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <sys/socket.h>
#include <arpa/inet.h>


int main(int argc, char* argv[])
{
    if (password_check(argc, argv) != 0) return EXIT_FAILURE;
    
    int client_fd;
    int server_fd;

    server_fd = create_server_socket();
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
    return EXIT_SUCCESS;
}
