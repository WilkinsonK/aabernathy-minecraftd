// System tools and settings for this project.

#ifndef H_SYSTEM_MGMT

// Max size of a filename.
#define C_MAX_FILEPATH_SIZE 512

// Max size of a char array.
#define C_MAX_VARCHAR_SIZE 256

#define notice_pre(prefix, color) color prefix C_NO_COLOR ": "

// Sends a message, as an mctool, to stdout.
#define noticef(mformat, ...) fprintf(stdout, notice_pre("mcserver", C_GREEN) mformat, __VA_ARGS__)

// Sends an output to stderr, then exits with the
// given error code.
#define cpanicf(mformat, code, ...) \
    fprintf(stderr, notice_pre("error", C_RED) mformat, __VA_ARGS__); \
    exit(code)

// Sends an output to stderr, then exits as
// failure.
#define panicf(mformat, ...) cpanicf(mformat, EXIT_FAILURE, __VA_ARGS__)

#define H_SYSTEM_MGMT
#endif // H_SYSTEM_MGMT
