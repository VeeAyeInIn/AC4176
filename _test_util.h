#ifndef AC4176__TEST_UTIL_H
#define AC4176__TEST_UTIL_H



#include <stdio.h>



/**
 * Reads in a value from a file to a buffer.
 *
 * @param buffer The buffer to store the contents in.
 * @param buffer_size The size of the buffer.
 * @param fp The file pointer.
 *
 * @return The amount of data read in.
 */
size_t pread(char* restrict buffer, size_t buffer_size, FILE* restrict fp);



#endif //AC4176__TEST_UTIL_H
