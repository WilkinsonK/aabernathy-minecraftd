/**
 * Start a server instance with the selected
 * server `JAR` file.
 * 
 * ENVIRONMENT VARIABLES
 * *********************
 * 
 * Below is a list of variable names this program
 * will attempt to lookup in the active
 * environment. If not found they will result in
 * making use of some assigned default, or be
 * skipped entirely.
 * 
 * MCSERVER_EXE: <string> The name, or path to
 * whatever binary will be used to start the
 * application. Default behavior is 'java'
 * 
 * MCSERVER_JAR: <string> The name or path to
 * whatever `JAR` file will be used to create
 * the server application.
 * 
 * MCSERVER_RAM_INI: <string> The inital amount
 * of memory to allocate for Minecraft server
 * startup.
 * 
 * MCSERVER_RAM_MAX: <string> The maximum amount
 * of memory the Minecraft server is allowed to
 * access.
*/

#define EXPECTED_ARGS_COUNT 1

#define MCDEFAULT_DEFAULT ""
#define MCDEFAULT_EXE "java"
#define MCDEFAULT_JAR "server/launcher-1.18.2.jar"
#define MCDEFAULT_NOGUI "nogui"
#define MCDEFAULT_RAM "1024M"

#define MCDEFAULT_STR_SIZE 64
#define MCDEFAULT_STR_SIZE_MAX 128
#define MCDEFAULT_STR_FMT "%s"

#ifndef SOURCE_DIR
#define SOURCE_DIR ""
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Target executable used to start the
 * server.
*/
char MCSERVER_EXE[MCDEFAULT_STR_SIZE];

/**
 * Target server `JAR` file run by the
 * target executable.
*/
char MCSERVER_JAR[MCDEFAULT_STR_SIZE];

/**
 * Initial amount of memory to allocate
 * to the Minecraft server.
*/
char MCSERVER_RAM_INI[MCDEFAULT_STR_SIZE];

/**
 * Maximum amount of memory the Minecraft
 * server is allowed to access at one time.
*/
char MCSERVER_RAM_MAX[MCDEFAULT_STR_SIZE];

/**
 * Placeholder for arguments passed to this
 * executable at runtime.
*/
char **MCSERVER_RUNTIME_ARGV;

/**
 * Placeholder for argument count passed
 * to this executable at runtime.
*/
int MCSERVER_RUNTIME_ARGC;


/**
 * Tries to parse some value from the
 * active environment. If this value
 * cannot be found, returns some default
 * value instead.
*/
char* server_getvalue(const char* envname, char* valdefault) {
    char* var_value = getenv(envname);

    if (var_value == NULL) {
        var_value = valdefault;
    }
    return var_value;
}


/**
 * Parses and assigns the value
 * to the target char array. Values
 * are first looked up in the active
 * environment, replaced with the
 * default if not found.
*/
void server_parsef(char* target, const char* valformat, char* envname, char* envdefault) {
    char buffer[MCDEFAULT_STR_SIZE];

    // If no format was passed,
    // use the default format setting.
    if (valformat == NULL) {
        valformat = MCDEFAULT_STR_FMT;
    }

    // If no default was passed,
    // use the default default setting.
    if (envdefault == NULL) {
        envdefault = MCDEFAULT_DEFAULT;
    }

    sprintf(buffer, valformat, server_getvalue(envname, envdefault));
    strcpy(target, buffer);
}


/**
 * Renders a collection of arguments as a
 * concatenated list ready for printing to
 * `stdout`.
*/
void server_render_argout(char* engine_args[], char* bufsep) {
    // String buffer values for
    // creating a render of the above
    // engine args. Cosmetic detail for
    // runtime readability.
    char sbuffer[MCDEFAULT_STR_SIZE_MAX] = "";
    char nbuffer[MCDEFAULT_STR_SIZE];

    int step = 0;
    do {
        // Parses the next value for the
        // string output.
        if (engine_args[step] == NULL) {
            strcpy(nbuffer, "\0");
        } else { sprintf(nbuffer, "'%s'", engine_args[step]); }

        // Check to see if the current
        // argument is the tail of the
        // values.
        if (engine_args[step] != NULL && engine_args[step + 1] != NULL) {
            strcat(nbuffer, bufsep);
        }

        // Append next buffer to the string
        // buffer.
        strcat(sbuffer, nbuffer);

        step++;
    } while (strcmp(nbuffer, "\0"));

    printf("SERVER_ARGS={%s}\n", sbuffer);
}


/**
 * Parses and assigns server variables
 * as what is necessary.
*/
void server_parse_envvars() {

    // target binaries.
    server_parsef(MCSERVER_EXE, NULL, "MCSERVER_EXE", MCDEFAULT_EXE);
    server_parsef(MCSERVER_JAR, "-jar %s", "MCSERVER_JAR", MCDEFAULT_JAR);

    // Memory related values.
    server_parsef(MCSERVER_RAM_INI, "-Xms%s", "MCSERVER_RAM_INI", MCDEFAULT_RAM);
    server_parsef(MCSERVER_RAM_MAX, "-Xmx%s", "MCSERVER_RAM_MAX", MCDEFAULT_RAM);
}


/**
 * Starts the server engine.
 * 
 * WARNING: Assumes all necessary
 * vars have been parsed and assigned.
*/
void server_start_engine() {
    // Collect arguments to pass to
    // executor.
    // char* engine_args[] = {
    //     MCSERVER_EXE,
    //     MCSERVER_RAM_INI,
    //     MCSERVER_RAM_MAX,
    //     MCSERVER_JAR,
    //     MCDEFAULT_NOGUI, NULL}; // Must terminate args with `NULL`.

    char* engine_args[] = {
        "which",
        MCSERVER_EXE, NULL};

    server_render_argout((char**)engine_args, ", ");

    // Call the executable with
    // arguments
    int ret = execvp(engine_args[0], engine_args);

    // Complain if something goes
    // wrong.
    if (ret == -1) { perror("execvp"); }
}


int main(int argc, char** argv, char** penv) {
    // Store our CLI arguments elsewhere.
    MCSERVER_RUNTIME_ARGC = argc;
    MCSERVER_RUNTIME_ARGV = argv;

    server_parse_envvars();
    server_start_engine();
    return 0;
}
