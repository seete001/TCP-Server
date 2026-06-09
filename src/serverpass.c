#include "serverpass.h"

#include <stdio.h>
#include <string.h>

int password_check(int argc, char **argv)
{
    if (argc < 2)
    {
        perror("Usage: ./server <password>");
        return 1;
    }

    else if (strcmp(argv[1], "123") != 0)
    {
        perror("Wrong password");
        return 1;
    }
    return 0;
}
