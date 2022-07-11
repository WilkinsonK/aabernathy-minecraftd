#include <stdio.h>
#include <stdlib.h>

#include "lib/colors.h"
#include "lib/server_system.h"
#include "lib/server_tools.h"

int main(int argc, char** argv)
{
    if (argc < 1)
    {
        panicf("missing parameter (server_version).", NULL);
    }

    int response = init_server(argv[1]);

    // Complain and bail if something goes wrong.
    if (response == -1)
    {
        panicf("server engine failed.", NULL);
    }

    return EXIT_SUCCESS;
}
