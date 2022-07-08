#include <stdio.h>
#include <stdlib.h>

#include "colors.h"
#include "server_system.h"


void panic(const char* message)
{
    panicc(message, EXIT_FAILURE);
}


void panicc(const char* message, int code)
{
    fprintf(stderr, C_RED "error" C_NO_COLOR ": %s\n", message);
    exit(code);
}
