#include <stdlib.h>
#include <stdio.h>

void load_file_to_string(const char* file_path, char** dst)
{
    // Create null streamptr.
    FILE* file = NULL;

    // Error handling.
    errno_t err;

    // Open the file and returns a pointer to the file stream associated with that file.
    // There are different mode to access the file:
    //      * "r" - Open a file for reading
    //      * "w" - Create a file for writing	
    //      * "a" - Append to a file
    if (0 != (err = fopen_s(&file, file_path, "rb"))) {
        printf("ERROR:: opened file name: \"%s\"\n", file_path);
        exit(1);
    }

    // -----------------------------------------------------------------------
    // `fopen_s` is in C11 standard, if compiler does not support C11, might write like this
    // 
    //    FILE *file = fopen(file_path, "rb");
    //    if (!file) {
    //        printf("ERROR:: opened file name: %s\n", file_path);
    //        exit(1);
    //    }
    //
    // -----------------------------------------------------------------------

    // Sets the file position indicator for the file stream stream to the value pointed to by offset.
    // ​0​ upon success, nonzero value otherwise
    // For second parameter, `long offset`, act differently by our open mode:
    //      * Binary files: Number of bytes to offset from origin.
    //      * Text files: Either zero, or a value returned by ftell.
    // This line of code mean `From the end of the file to the begin`
    fseek(file, 0, SEEK_END);

    // Get the current file text size
    int length = ftell(file);

    // Set file stream to begin
    rewind(file);

    // Allocate space for the text, +1 for the `\0`
    *dst = calloc(length + 1, sizeof(char));

    // Read file
    // Second parameter is the byte of each element to be read
    // Third parameter is the count of elements 
    fread(*dst, 1, length, file);

    // Remeber to close the file
    fclose(file);
}

//// TEST ////
int main() {

    char* text = NULL;

    load_file_to_string("res/Three_little_pigs.txt", &text);

    printf("The story begin:\n%s", text);

    return 0;
}