#include <malloc.h>
#include <memory.h>
#include <string.h>
#include "bignumber.h"



#define MAX(x, y) ((x > y) ? x : y)
#define MIN(x, y) ((x > y) ? y : x)



/*
 * Constants
 */



static uintx_t zero;
static uintx_t one;



/*
 * Constants Getters
 */



const uintx_t* uintx_zero(void) {

    if (zero.size == 0) {
        uintx_init(&zero);
        *zero.data = 0;
    }

    return &zero;

}



const uintx_t* uintx_one(void) {

    if (one.size == 0) {
        uintx_init(&one);
        *one.data = 1;
    }

    return &one;

}



/*
 * Memory
 */



uintx_t* uintx_init(uintx_t* bn) {
    bn->data = calloc(1, sizeof(uint32_t));
    bn->size = 1;
    return bn;
}



void uintx_free(uintx_t* bn) {
    free(bn->data);
    bn->data = NULL;
    bn->size = 0;
}



FILE* uintx_print(FILE* out, const uintx_t* a) {

    char output[a->size * 8 + 1];
    output[a->size * 8] = '\0';

    for (size_t i = 0; i < a->size; i++) {
        sprintf(output + (i * 8), "%08x", a->data[i]);
    }

    fprintf(out, "0x%s", output);

    return out;

}



uintx_t* uintx_set_size(uintx_t* a, size_t size) {

    if (size == 0) {
        uintx_free(a);
        return NULL;
    }

    uint32_t* resized_data = realloc(a->data, size * sizeof(uint32_t));
    if (resized_data == NULL) {
        return a;
    }

    a->data = resized_data;
    a->size = size;

    return a;

}



uintx_t* uintx_trim(uintx_t* a) {

    size_t trimmed_size;
    for (trimmed_size = a->size; trimmed_size > 1; --trimmed_size) {
        if (a->data[trimmed_size - 1] != 0) {
            break;
        }
    }

    uint32_t* trimmed_data = realloc(a->data, trimmed_size * sizeof(uint32_t));
    if (trimmed_data == NULL) {
        return a;
    }

    a->data = trimmed_data;
    a->size = trimmed_size;

    return a;

}



/*
 * Setting
 */



uintx_t* uintx_parse_hex(uintx_t* a, const char* restrict str) {

    // Get the length of the string.
    size_t hex_length = (str == NULL) ? 0 : strlen(str);

    // Treat a NULL string as 0.
    if (hex_length == 0) {
        uint32_t* new_data = realloc(a->data, sizeof(uint32_t));
        if (new_data == NULL) {
            return NULL;
        }
        *new_data = 0;
        a->data = new_data;
        a->size = 1;
        return a;
    }

    // Remove the "0x" prefix if it exists.
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        str        += 2;
        hex_length -= 2;
    }

    // Remove redundant leading zeros.
    while (str[0] == '0') {
        str++;
        hex_length--;
    }

    // Treat a NULL string as 0.
    if (hex_length == 0) {
        uint32_t* new_data = realloc(a->data, sizeof(uint32_t));
        if (new_data == NULL) {
            return NULL;
        }
        *new_data = 0;
        a->data = new_data;
        a->size = 1;
        return a;
    }

    // The amount of blocks (8 hex per uint32_t) to parse.
    size_t blocks = (hex_length + 7) / 8;
    uintx_set_size(a, blocks);

    // Read in each block of hex, converting it to a uint32.
    for (size_t i = 0; i < blocks; i++) {
        size_t start = i * 8;
        size_t end = MIN(hex_length, start + 8);
        char temp[9] = { '\0' };
        strncpy(temp, str + start, end - start);
        a->data[i] = (uint32_t) strtoul(temp, NULL, 16);
    }

    return uintx_trim(a);

}



uintx_t* uintx_parse_dec(uintx_t* a, const char* restrict str) {
    return a;
}



uintx_t* uintx_from_uint32(uintx_t* a, uint32_t b) {
    uintx_set_size(a, 1);
    a->data[0] = b;
    return a;
}



uintx_t* uintx_copy(uintx_t* a, const uintx_t* b) {
    uintx_set_size(a, b->size);
    memcpy(a->data, b->data, b->size * sizeof(uint32_t));
    return a;
}



/*
 * Bitwise Operations
 */



uintx_t* uintx_not(uintx_t* result, const uintx_t* a) {
    for (size_t i = 0; i < a->size; i++) {
        result->data[i] = ~a->data[i];
    }
    return result;
}



uintx_t* uintx_and(uintx_t* result, const uintx_t* a, const uintx_t* b) {

    size_t max = MAX(a->size, b->size);

    if (result->size != max) {
        uintx_set_size(result, max);
    }

    for (size_t i = 0; i < max; i++) {
        result->data[i] = a->data[i] & b->data[i];
    }

    return result;

}



uintx_t* uintx_nand(uintx_t* result, const uintx_t* a, const uintx_t* b) {

    size_t max = MAX(a->size, b->size);

    if (result->size != max) {
        uintx_set_size(result, max);
    }

    for (size_t i = 0; i < max; i++) {
        result->data[i] = ~(a->data[i] & b->data[i]);
    }

    return result;

}



uintx_t* uintx_or(uintx_t* result, const uintx_t* a, const uintx_t* b) {

    size_t max = MAX(a->size, b->size);

    if (result->size != max) {
        uintx_set_size(result, max);
    }

    for (size_t i = 0; i < max; i++) {
        result->data[i] = a->data[i] | b->data[i];
    }

    return result;

}



uintx_t* uintx_xor(uintx_t* result, const uintx_t* a, const uintx_t* b) {

    size_t max = MAX(a->size, b->size);

    if (result->size != max) {
        uintx_set_size(result, max);
    }

    for (size_t i = 0; i < max; i++) {
        result->data[i] = a->data[i] ^ b->data[i];
    }

    return result;

}



uintx_t* uintx_nor(uintx_t* result, const uintx_t* a, const uintx_t* b) {

    size_t max = MAX(a->size, b->size);

    if (result->size != max) {
        uintx_set_size(result, max);
    }

    for (size_t i = 0; i < max; i++) {
        result->data[i] = ~(a->data[i] | b->data[i]);
    }

    return result;

}



uintx_t* uintx_shift_left(uintx_t* result, const uintx_t* a, size_t bits) {

    size_t block_shift = bits / 32;
    size_t bit_shift   = bits % 32;

    uintx_t temp_result;
    uintx_init(&temp_result);

    size_t new_size = a->size + block_shift + (bit_shift > 0 ? 1 : 0);
    uintx_set_size(&temp_result, new_size);

    memset(temp_result.data, 0, new_size * sizeof(uint32_t));

    for (size_t i = 0; i < a->size; i++) {

        size_t target_index = i + block_shift;
        temp_result.data[target_index] |= a->data[i] << bit_shift;

        if (bit_shift > 0 && target_index + 1 < new_size) {
            temp_result.data[target_index + 1] |= a->data[i] >> (32 - bit_shift);
        }

    }

    // Copy temp_result to result.
    uintx_trim(&temp_result);
    uintx_copy(result, &temp_result);

    uintx_free(&temp_result);

    return result;

}



uintx_t* uintx_shift_right(uintx_t* result, const uintx_t* a, size_t bits) {

    size_t block_shift = bits / 32;
    size_t bit_shift   = bits % 32;

    return result;

}



uintx_t* uintx_rotate_left(uintx_t* result, const uintx_t* a, size_t bits) {

    size_t block_shift = bits / 32;
    size_t bit_shift   = bits % 32;

    return result;

}



uintx_t* uintx_rotate_right(uintx_t* result, const uintx_t* a, size_t bits) {

    size_t block_shift = bits / 32;
    size_t bit_shift   = bits % 32;

    return result;

}



size_t uintx_msb(const uintx_t* a) {

    // Empty or values of zero.
    if (a->size == 0 || (a->size == 1 && a->data[0] == 0)) {
        return 0;
    }

    for (size_t i = a->size; i > 0; --i) {
        uint32_t value = a->data[i - 1];

        if (value != 0) {
            return (i - 1) * 32 + (31 - __builtin_clz(value));
        }

    }

    return 0;

}



size_t uintx_lsb(const uintx_t* a) {
    for (size_t i = 0; i < a->size; i++) {
        if (a->data[i] != 0) {
            return __builtin_ctz(a->data[i]) + (i * 32);
        }
    }
    return 0;
}



int uintx_bitget(const uintx_t* a, size_t index) {

    size_t block = index / 32;
    size_t offset = index % 32;

    if (block >= a->size) {
        return 0;
    }

    return (int) (a->data[block] >> offset) & 1;

}



void uintx_bitset(uintx_t* a, size_t index, int value) {

    size_t block = index / 32;
    size_t offset = index % 32;

    if (block >= a->size) {
        uintx_set_size(a, block + 1);
    }

    if (value) {
        a->data[block] |= (1U << offset);
    } else {
        a->data[block] &= ~(1U << offset);
    }

}



void uintx_bitflip(uintx_t* a, size_t index) {

    size_t block = index / 32;
    size_t offset = index % 32;

    if (block >= a->size) {
        uintx_set_size(a, block + 1);
    }

    a->data[block] ^= (1U << offset);

}



/*
 * Logical Operations
 */



bool uintx_equal(const uintx_t* a, const uintx_t* b) {

    if (a->size != b->size) {
        return false;
    }

    for (size_t i = 0; i < a->size; i++) {
        if (a->data[i] != b->data[i]) {
            return false;
        }
    }
    
    return true;

}



bool uintx_lt(const uintx_t* a, const uintx_t* b) {
    return !uintx_geq(a, b);
}



bool uintx_gt(const uintx_t* a, const uintx_t* b) {

    size_t msb_a = uintx_msb(a);
    size_t msb_b = uintx_msb(b);

    if (msb_a > msb_b) {
        return true;
    } else if (msb_a < msb_b) {
        return false;
    }

    for (size_t i = msb_a; i != UINT64_MAX; i--) {

        bool bit_a = uintx_bitget(a, i);
        bool bit_b = uintx_bitget(b, i);

        if (bit_a > bit_b) {
            return true;
        } else if (bit_a < bit_b) {
            return false;
        }

    }

    return false; // Equality

}



bool uintx_leq(const uintx_t* a, const uintx_t* b) {
    return !uintx_gt(a, b);
}



bool uintx_geq(const uintx_t* a, const uintx_t* b) {
    return uintx_gt(a, b) || uintx_equal(a, b);
}



/*
 * Arithmetic Operations
 */



uintx_t* uintx_add(uintx_t* result, const uintx_t* a, const uintx_t* b) {

    size_t max = a->size > b->size ? a->size : b->size;
    uintx_set_size(result, max);

    uint32_t overflow = 0;
    for (size_t i = 0; i < max; i++) {
        uint64_t partial_sum = (uint64_t) overflow;

        if (i < a->size) {
            partial_sum += a->data[i];
        }

        if (i < b->size) {
            partial_sum += b->data[i];
        }

        result->data[i] = (uint32_t) partial_sum;
        overflow = partial_sum >> 32;

    }

    if (overflow) {
        uintx_set_size(result, max + 1);
        result->data[max] = overflow;
    }

    return uintx_trim(result);

}



uintx_t* uintx_sub(uintx_t* result, const uintx_t* a, const uintx_t* b) {

    if (a->size < b->size) {
        return NULL;
    }

    uintx_set_size(result, a->size);
    uint32_t borrow = 0;

    for (size_t i = 0; i < a->size; i++) {

        uint64_t difference = (uint64_t) a->data[i] - borrow;

        if (i < b->size) {
            difference -= b->data[i];
        }

        if (difference > UINT32_MAX) {
            borrow = 1;
            difference += (1ULL << 32);
        } else {
            borrow = 0;
        }

        result->data[i] = (uint32_t) difference;

    }

    return uintx_trim(result);

}



uintx_t* uintx_div(uintx_t* result, const uintx_t* a, const uintx_t* b) {

    if (b->size == 1 && b->data[0] == 0) {
        return NULL;
    }

    uintx_t temp_result;
    uintx_t remainder;

    uintx_init(&remainder);
    uintx_init(&temp_result);

    uintx_set_size(&temp_result, a->size);
    memset(temp_result.data, 0, temp_result.size * sizeof(uint32_t));

    // Perform long division bit by bit.
    size_t msb_a = uintx_msb(a);
    size_t msb_b = uintx_msb(b);

    if (msb_a < msb_b) {
        goto div_cleanup;
    }

    for (size_t bit = msb_a; bit != UINT64_MAX; bit--) {
        uintx_shift_left(&remainder, &remainder, 1);
        uintx_bitset(&remainder, 0, uintx_bitget(a, bit));

        if (uintx_geq(&remainder, b)) {
            uintx_sub(&remainder, &remainder, b);
            uintx_bitset(&temp_result, bit, 1);
        }
    }

    div_cleanup: // Label to reduce nesting.

    uintx_trim(&temp_result);
    uintx_copy(result, &temp_result);

    uintx_free(&temp_result);
    uintx_free(&remainder);

    return result;

}



uintx_t* uintx_mul(uintx_t* result, const uintx_t* a, const uintx_t* b) {

    uintx_t temp_result;
    temp_result.size = a->size + b->size;
    temp_result.data = calloc(temp_result.size, sizeof(uint32_t));
    if (temp_result.data == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < a->size; i++) {

        uint64_t carry = 0;
        for (size_t j = 0; j < b->size; j++) {
            uint64_t product = (uint64_t) a->data[i] * b->data[j] + temp_result.data[i + j] + carry;
            temp_result.data[i + j] = (uint32_t) product;
            carry = product >> 32;
        }
        temp_result.data[i + b->size] = (uint32_t) carry;

    }

    uintx_copy(result, &temp_result);
    free(temp_result.data);

    return uintx_trim(result);
    
}



uintx_t* uintx_pow(uintx_t* result, const uintx_t* a, const uintx_t* b) {

    uintx_t temp_result, base;

    uintx_init(&temp_result);
    uintx_init(&base);

    uintx_parse_hex(&temp_result, "0x1");
    uintx_copy(&base, a);

    size_t msb = uintx_msb(b);

    for (size_t bit = 0; bit <= msb; bit++) {

        // r <- r * a
        if (uintx_bitget(b, bit)) {
            uintx_mul(&temp_result, &temp_result, &base);
        }

        // r <- r * r
        uintx_mul(&base, &base, &base);

    }

    uintx_copy(result, &temp_result);

    uintx_free(&temp_result);
    uintx_free(&base);

    return uintx_trim(result);

}



uintx_t* uintx_mod(uintx_t* result, const uintx_t* a, const uintx_t* b) {

    // Division by zero.
    if (b->size == 1 && b->data[0] == 0) {
        return NULL;
    }

    uintx_t quotient;
    uintx_t remainder;

    uintx_init(&quotient);
    uintx_init(&remainder);

    uintx_div(&quotient, a, b);
    uintx_mul(&remainder, &quotient, b);
    uintx_sub(&remainder, a, &remainder);;

    uintx_copy(result, &remainder);

    uintx_free(&quotient);
    uintx_free(&remainder);

    return result;

}



uintx_t* uintx_sqmul(uintx_t* result, const uintx_t* a, const uintx_t* b, const uintx_t* m) {

    uintx_t temp_result, base;

    uintx_init(&temp_result);
    uintx_init(&base);

    uintx_parse_hex(&temp_result, "0x1");
    uintx_copy(&base, a);

    size_t msb = uintx_msb(b);

    for (size_t bit = 0; bit <= msb; bit++) {

        // r <- r * a
        if (uintx_bitget(b, bit)) {
            uintx_mul(&temp_result, &temp_result, &base);
            uintx_mod(&temp_result, &temp_result, m);
        }

        // r <- r * r
        uintx_mul(&base, &base, &base);
        uintx_mod(&temp_result, &temp_result, m);

    }

    uintx_copy(result, &temp_result);

    uintx_free(&temp_result);
    uintx_free(&base);

    return uintx_trim(result);

}