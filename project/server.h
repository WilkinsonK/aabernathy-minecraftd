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

#ifndef H_SERVER_MGMT

// Max size of a filename.
#define C_MAX_FILEPATH_SIZE 512

// Max size of a char array.
#define C_MAX_VARCHAR_SIZE 256

// Path to executable directory.
#ifndef V_SOURCE_DIR
#define V_SOURCE_DIR "."
#endif

// Java executable path
#ifndef V_MCDEFAULT_SERVER_EXE
#define V_MCDEFAULT_SERVER_EXE "java"
#endif

// JAR file containing server engine class.
// Not an absolute path.
#ifndef V_MCDEFAULT_SERVER_CLS
#define V_MCDEFAULT_SERVER_CLS "server-%s.jar"
#endif

// Default memory allocation size.
#ifndef V_MCDEFAULT_MEMORY
#define V_MCDEFAULT_MEMORY "1024M"
#endif

#ifndef V_DEBUG_MODE
#define V_DEBUG_MODE 0
#endif

#define ARRAY_SIZE(ARRAY, T) (sizeof(ARRAY)/sizeof(T))

// Container for launch related values.
typedef struct serverargs_t {
    // Java executable.
    char executable[C_MAX_VARCHAR_SIZE];

    // JAR file containing server engine class.
    // Not an absolute path.
    char server_cls[C_MAX_FILEPATH_SIZE];

    // Initial memory for server startup.
    char memory_ini[C_MAX_VARCHAR_SIZE];

    // Maximum allocated server memory.
    char memory_max[C_MAX_VARCHAR_SIZE];
} serverargs_t;

// Initialize server engine.
int init_server();

#define H_SERVER_MGMT
#endif // H_SERVER_MGMT
