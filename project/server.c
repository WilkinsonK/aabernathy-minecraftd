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
#define MCDEFAULT_RAM "1024M"
#define MCDEFAULT_JAR "server-1.18.1.jar"

#define MCDEFAULT_STR_SIZE 24
#define MCDEFAULT_STR_FMT "%s"

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
void server_parsef(char * target, const char * valformat, char * envname, char * envdefault) {
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
 * Parses and assigns server variables
 * as what is necessary.
*/
void server_parse_envvars() {

    // target binaries.
    server_parsef(MCSERVER_EXE, NULL, "MCSERVER_EXE", MCDEFAULT_EXE);
    server_parsef(MCSERVER_JAR, NULL, "MCSERVER_JAR", MCDEFAULT_JAR);

    // Memory related values.
    server_parsef(MCSERVER_RAM_INI, "-Xms%s", "MCSERVER_RAM_INI", MCDEFAULT_RAM);
    server_parsef(MCSERVER_RAM_MAX, "-Xmx%s", "MCSERVER_RAM_MAX", MCDEFAULT_RAM);
}


int main(int argc, char** argv, char** penv) {
    server_parse_envvars();
    printf("INITIAL RAM: %s\n", MCSERVER_RAM_INI);
    printf("MAXIMUM RAM: %s\n", MCSERVER_RAM_MAX);

    // char *args[] = {MCSERVER_JAR, MCSERVER_RAM_INI, MCSERVER_RAM_MAX}
    // execvp(MCSERVER_EXE)
    return 0;
}
