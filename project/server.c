#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "colors.h"
#include "server.h"

// Global instance of server arguments.
static serverargs_t global_sargs;


// Raise an error message and bail.
void panic(const char* message)
{
    fprintf(stderr, C_RED "error" C_NO_COLOR ": %s\n", message);
    exit(EXIT_FAILURE);
}


// Parse some value from the environment,
// applying it to the target. If target variable
// name is not found, apply the default.
void parse_senv(const char* name, char* default_v, char* target)
{
    char* value = (char*)getenv(name);

    if (value == NULL) {
        value = default_v;
    }
    strcpy(target, value);
}


// Modify the target string to match the given
// format.
void format_repl(const char* format, char* target)
{
    char buffer[C_MAX_VARCHAR_SIZE];
    sprintf(buffer, format, target);
    strcpy(target, buffer);
}


// Modify the target string to be a render of the
// values in a given array, joined by a given
// separator.
//
// NOTE: the given array must terminate using an
// empty string.
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

// Initialize default server values.
static void initialize_sargs(serverargs_t* sargs)
{
    // Apply program defaults.
    parse_senv("MCSERVER_EXE", V_MCDEFAULT_SERVER_EXE, sargs->executable);
    parse_senv("MCSERVER_JAR", V_MCDEFAULT_SERVER_CLS, sargs->server_cls);
    parse_senv("MCSERVER_RAM_INI", V_MCDEFAULT_MEMORY, sargs->memory_ini);
    parse_senv("MCSERVER_RAM_MAX", V_MCDEFAULT_MEMORY, sargs->memory_max);

    // Format specific values.
    format_repl("-Xms%s", sargs->memory_ini);
    format_repl("-Xmx%s", sargs->memory_max);

    // Format path values.
    format_join(
        (char*[]){V_SOURCE_DIR, "jars", sargs->server_cls, ""},
        "/", sargs->server_cls);
}


int init_server(char* server_version)
{
    if (server_version == NULL)
    {
        panic("invalid server version.");
    }

    // Initialize parameters.
    initialize_sargs(&global_sargs);

    // Identify which server JAR to use.
    char server_cls[C_MAX_FILEPATH_SIZE];
    sprintf(server_cls, global_sargs.server_cls, server_version);

    char* engine_sargs[] = {
        global_sargs.executable,
        global_sargs.memory_ini,
        global_sargs.memory_max,
        "-jar",
        server_cls,
        "nogui", NULL}; // Must terminate args with `NULL`.

    return execvp(global_sargs.executable, engine_sargs);
}


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
