#include "_test_util.h"
#include "../src/bignumber.h"



size_t pread(char* restrict buffer, size_t buffer_size, FILE* restrict fp) {

    if (fp == NULL) {
        return -1;
    }

    return fread(buffer, sizeof(char), buffer_size, fp);

}