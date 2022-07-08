#include <stdlib.h>

#include "server_system.h"
#include "server_tools.h"

int main(int argc, char** argv)
{
    if (argc < 1)
    {
        panic("missing parameter (server_version).");
    }

    int response = init_server(argv[1]);

    // Complain and bail if something goes wrong.
    if (response == -1)
    {
        panic("server engine failed.");
    }

    return EXIT_SUCCESS;
}
