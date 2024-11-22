#include "modnumber.h"



#define MAX(x, y) ((x > y) ? x : y)
#define MIN(x, y) ((x > y) ? y : x)



/*
 * Constants
 */



static uintmod_t zero;
static uintmod_t one;



/*
 * Constants Getters
 */



//const uintmod_t* uintmod_zero(void) {
//
//    if (zero.value.size == 0) {
//        uintmod_init(&zero);
//        *zero.value.data = 0;
//    }
//
//    return &zero;
//
//}



//const uintmod_t* uintmod_one(void) {
//
//    if (one.size == 0) {
//        uintmod_init(&one);
//        *one.data = 1;
//    }
//
//    return &one;
//
//}



/*
 * Memory
 */



uintmod_t* uintmod_init(uintmod_t* bn) {
    uintx_init(&bn->value);
    uintx_init(&bn->modulo);
    return bn;
}



void uintmod_free(uintmod_t* bn) {
    uintx_free(&bn->value);
    uintx_free(&bn->modulo);
}



FILE* uintmod_print(FILE* out, const uintmod_t* a) {

//    char output[a->size * 8 + 1];
//    output[a->size * 8] = '\0';
//
//    for (size_t i = 0; i < a->size; i++) {
//        sprintf(output + (i * 8), "%08x", a->data[i]);
//    }
//
//    fprintf(out, "0x%s", output);

    return out;

}



/*
 * Setting
 */



//uintmod_t* uintmod_parse_hex(uintmod_t* a, const char* restrict str_val, const char* restrict str_mod) {
//
//    // Get the length of the string.
//    size_t hex_length = (str == NULL) ? 0 : strlen(str);
//
//    // Treat a NULL string as 0.
//    if (hex_length == 0) {
//        uint32_t* new_data = realloc(a->data, sizeof(uint32_t));
//        if (new_data == NULL) {
//            return NULL;
//        }
//        *new_data = 0;
//        a->data = new_data;
//        a->size = 1;
//        return a;
//    }
//
//    // Remove the "0x" prefix if it exists.
//    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
//        str        += 2;
//        hex_length -= 2;
//    }
//
//    // Remove redundant leading zeros.
//    while (str[0] == '0') {
//        str++;
//        hex_length--;
//    }
//
//    // Treat a NULL string as 0.
//    if (hex_length == 0) {
//        uint32_t* new_data = realloc(a->data, sizeof(uint32_t));
//        if (new_data == NULL) {
//            return NULL;
//        }
//        *new_data = 0;
//        a->data = new_data;
//        a->size = 1;
//        return a;
//    }
//
//    // The amount of blocks (8 hex per uint32_t) to parse.
//    size_t blocks = (hex_length + 7) / 8;
//    uintmod_set_size(a, blocks);
//
//    // Read in each block of hex, converting it to a uint32.
//    for (size_t i = 0; i < blocks; i++) {
//        size_t start = i * 8;
//        size_t end = MIN(hex_length, start + 8);
//        char temp[9] = { '\0' };
//        strncpy(temp, str + start, end - start);
//        a->data[i] = (uint32_t) strtoul(temp, NULL, 16);
//    }
//
//    return uintmod_trim(a);
//
//}



uintmod_t* uintmod_parse_dec(uintmod_t* a, const char* restrict str) {
    return NULL;
}



uintmod_t* uintmod_from_uint32(uintmod_t* a, uint32_t b) {
    return NULL; // uintx_from_uint32()
}



uintmod_t* uintmod_copy(uintmod_t* a, const uintmod_t* b) {
    uintx_copy(&a->value, &b->value);
    uintx_copy(&a->modulo, &b->modulo);
    return a;
}



/*
 * Bitwise Operations
 */



uintmod_t* uintmod_not(uintmod_t* result, const uintmod_t* a) {

    // Make sure result is under the same modulo.
    uintx_copy(&result->modulo, &a->modulo);

    // Compute, then mod.
    uintx_not(&result->value, &a->value);
    uintx_mod(&result->value, &result->value, &result->modulo);

    return result;

}



uintmod_t* uintmod_and(uintmod_t* result, const uintmod_t* a, const uintmod_t* b) {

    // Make sure result is under the same modulo.
    uintx_copy(&result->modulo, &a->modulo);

    // Compute, then mod.
    uintx_and(&result->value, &a->value, &b->value);
    uintx_mod(&result->value, &result->value, &result->modulo);

    return result;

}



uintmod_t* uintmod_nand(uintmod_t* result, const uintmod_t* a, const uintmod_t* b) {

    // Make sure result is under the same modulo.
    uintx_copy(&result->modulo, &a->modulo);

    // Compute, then mod.
    uintx_nand(&result->value, &a->value, &b->value);
    uintx_mod(&result->value, &result->value, &result->modulo);

    return result;

}



uintmod_t* uintmod_or(uintmod_t* result, const uintmod_t* a, const uintmod_t* b) {

    // Make sure result is under the same modulo.
    uintx_copy(&result->modulo, &a->modulo);

    // Compute, then mod.
    uintx_or(&result->value, &a->value, &b->value);
    uintx_mod(&result->value, &result->value, &result->modulo);

    return result;

}



uintmod_t* uintmod_xor(uintmod_t* result, const uintmod_t* a, const uintmod_t* b) {

    // Make sure result is under the same modulo.
    uintx_copy(&result->modulo, &a->modulo);

    // Compute, then mod.
    uintx_xor(&result->value, &a->value, &b->value);
    uintx_mod(&result->value, &result->value, &result->modulo);

    return result;

}



uintmod_t* uintmod_nor(uintmod_t* result, const uintmod_t* a, const uintmod_t* b) {

    // Make sure result is under the same modulo.
    uintx_copy(&result->modulo, &a->modulo);

    // Compute, then mod.
    uintx_nor(&result->value, &a->value, &b->value);
    uintx_mod(&result->value, &result->value, &result->modulo);

    return result;

}



uintmod_t* uintmod_shift_left(uintmod_t* result, const uintmod_t* a, size_t bits) {

    // Make sure result is under the same modulo.
    uintx_copy(&result->modulo, &a->modulo);

    // Compute, then mod.
    uintx_shift_left(&result->value, &a->value, bits);
    uintx_mod(&result->value, &result->value, &result->modulo);

    return result;

}



uintmod_t* uintmod_shift_right(uintmod_t* result, const uintmod_t* a, size_t bits) {

    size_t block_shift = bits / 32;
    size_t bit_shift   = bits % 32;

    return result;

}



uintmod_t* uintmod_rotate_left(uintmod_t* result, const uintmod_t* a, size_t bits) {

    size_t block_shift = bits / 32;
    size_t bit_shift   = bits % 32;

    return result;

}



uintmod_t* uintmod_rotate_right(uintmod_t* result, const uintmod_t* a, size_t bits) {

    size_t block_shift = bits / 32;
    size_t bit_shift   = bits % 32;

    return result;

}



size_t uintmod_msb(const uintmod_t* a) {
    return uintx_msb(&a->value);
}



size_t uintmod_lsb(const uintmod_t* a) {
    return uintx_lsb(&a->value);
}



int uintmod_bitget(const uintmod_t* a, size_t index) {
    return uintx_bitget(&a->value, index);
}



void uintmod_bitset(uintmod_t* a, size_t index, int value) {
    uintx_bitset(&a->value, index, value);
    uintx_mod(&a->value, &a->value, &a->modulo);
}



void uintmod_bitflip(uintmod_t* a, size_t index) {
    uintx_bitflip(&a->value, index);
    uintx_mod(&a->value, &a->value, &a->modulo);
}



/*
 * Logical Operations
 */



bool uintmod_equal(const uintmod_t* a, const uintmod_t* b) {
    return uintx_equal(&a->value, &b->value);
}



bool uintmod_lt(const uintmod_t* a, const uintmod_t* b) {
    return !uintmod_geq(a, b);
}



bool uintmod_gt(const uintmod_t* a, const uintmod_t* b) {
    return uintx_gt(&a->value, &b->value);
}



bool uintmod_leq(const uintmod_t* a, const uintmod_t* b) {
    return !uintmod_gt(a, b);
}



bool uintmod_geq(const uintmod_t* a, const uintmod_t* b) {
    return uintmod_gt(a, b) || uintmod_equal(a, b);
}



/*
 * Arithmetic Operations
 */



uintmod_t* uintmod_add(uintmod_t* result, const uintmod_t* a, const uintmod_t* b) {

    // Make sure result is under the same modulo.
    uintx_copy(&result->modulo, &a->modulo);

    // Compute, then mod.
    uintx_add(&result->value, &a->value, &b->value);
    uintx_mod(&result->value, &result->value, &result->modulo);

    return result;

}



uintmod_t* uintmod_sub(uintmod_t* result, const uintmod_t* a, const uintmod_t* b) {

    // Make sure result is under the same modulo.
    uintx_copy(&result->modulo, &a->modulo);

    // Compute, then mod.
    uintx_sub(&result->value, &a->value, &b->value);
    uintx_mod(&result->value, &result->value, &result->modulo);

    return result;

}



uintmod_t* uintmod_div(uintmod_t* result, const uintmod_t* a, const uintmod_t* b) {

    // Make sure result is under the same modulo.
    uintx_copy(&result->modulo, &a->modulo);

    // Compute, then mod.
    uintx_div(&result->value, &a->value, &b->value);
    uintx_mod(&result->value, &result->value, &result->modulo);

    return result;

}



uintmod_t* uintmod_mul(uintmod_t* result, const uintmod_t* a, const uintmod_t* b) {

    // Make sure result is under the same modulo.
    uintx_copy(&result->modulo, &a->modulo);

    // Compute, then mod.
    uintx_mul(&result->value, &a->value, &b->value);
    uintx_mod(&result->value, &result->value, &result->modulo);

    return result;

}



uintmod_t* uintmod_pow(uintmod_t* result, const uintmod_t* a, const uintmod_t* b) {

    uintmod_t temp_result, base;

    uintmod_init(&temp_result);
    uintmod_init(&base);

    // uintmod_parse_hex(&temp_result, "0x1");
    uintmod_copy(&base, a);

    size_t msb = uintmod_msb(b);

    for (size_t bit = 0; bit <= msb; bit++) {

        // r <- r * a
        if (uintmod_bitget(b, bit)) {
            uintmod_mul(&temp_result, &temp_result, &base);
        }

        // r <- r * r
        uintmod_mul(&base, &base, &base);

    }

    uintmod_copy(result, &temp_result);

    uintmod_free(&temp_result);
    uintmod_free(&base);

    return result;

}