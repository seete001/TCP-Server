#include "auth.h"

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#define PASSBUFF 64



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
