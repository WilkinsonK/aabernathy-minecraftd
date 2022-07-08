// System tools and settings for this project.

#ifndef H_SYSTEM_MGMT

// Max size of a filename.
#define C_MAX_FILEPATH_SIZE 512

// Max size of a char array.
#define C_MAX_VARCHAR_SIZE 256

// Sends an output to stderr, then exits as
// failure.
void panic(const char* message);

// Sends an output to stderr, then exits with the
// given error code.
void panicc(const char* message, int code);

#define H_SYSTEM_MGMT
#endif // H_SYSTEM_MGMT
