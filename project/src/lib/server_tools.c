#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "colors.h"
#include "server_format.h"
#include "server_system.h"
#include "server_tools.h"

// Global instance of server arguments.
static serverargs_t global_sargs;


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


// Modify the target string to be a render of the
// values in a given array, joined by a given
// separator.
//
// NOTE: the given array must terminate using an
// empty string.


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
        panicf("invalid server version.", NULL);
    }

    // Initialize parameters.
    initialize_sargs(&global_sargs);

    // Identify which server JAR to use.
    char server_cls[C_MAX_FILEPATH_SIZE];
    sprintf(server_cls, global_sargs.server_cls, server_version);

    noticef(
        "starting server target:\n"
        "  version:     '%s'\n"
        "  initial mem: %s\n"
        "  maximum mem: %s\n",
        server_version, global_sargs.memory_ini, global_sargs.memory_max);

    char* engine_sargs[] = {
        global_sargs.executable,
        global_sargs.memory_ini,
        global_sargs.memory_max,
        "-jar",
        server_cls,
        "nogui", NULL}; // Must terminate args with `NULL`.

    return execvp(global_sargs.executable, engine_sargs);
}
