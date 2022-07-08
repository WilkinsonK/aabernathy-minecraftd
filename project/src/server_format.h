// Used for string formatting and string
// replacements.

#ifndef H_FORMAT_MGMT


// Modify the target string to match the given
// format.
void format_repl(const char* format, char* target);

// Modify the target string to be a render of the
// values in a given array, joined by a given
// separator.
//
// NOTE: the given array must terminate using an
// empty string.
void format_join(char* components[], char* separator, char* target);

#define H_FORMAT_MGMT
#endif // H_FORMAT_MGMT
