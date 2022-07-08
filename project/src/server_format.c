#include <stdio.h>
#include <string.h>

#include "server_format.h"
#include "server_system.h"

void format_repl(const char* format, char* target)
{
    char buffer[C_MAX_VARCHAR_SIZE];
    sprintf(buffer, format, target);
    strcpy(target, buffer);
}


void format_join(char* components[], char* separator, char* target)
{
    // Render of formatted string.
    char sbuffer[C_MAX_FILEPATH_SIZE] = "";

    // Substring sentinels.
    char nbuffer0[C_MAX_VARCHAR_SIZE];
    char nbuffer1[C_MAX_VARCHAR_SIZE];

    int step = 0;
    do {
        strcpy(nbuffer0, components[step]);
        strcpy(nbuffer1, components[step + 1]);

        if (strcmp(nbuffer1, "\0")) 
        {
            strcat(nbuffer0, separator);
        }

        strcat(sbuffer, nbuffer0);
        step += 1;

    // strcmp behaves in the opposite way one
    // might initially expect... This ensures
    // nbuffer1 != "\0"
    } while (strcmp(nbuffer1, "\0"));

    // Finalize render by applying to the target.
    strcpy(target, sbuffer);
}
