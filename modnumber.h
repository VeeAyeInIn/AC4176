#ifndef MODNUMBER_H
#define MODNUMBER_H



#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "bignumber.h"



/*
 * Data Structures
 */



/**
 * A data-type similar to uints from `stdint.h`. A uintmod stores an unspecified amount of data, in the form of uint32s.
 */
typedef struct uintmod {
    uintx_t value;
    uintx_t modulo;
} uintmod_t;



/*
 * Constants Getters
 */



const uintmod_t* uintmod_zero(void);



const uintmod_t* uintmod_one(void);



/*
 * Memory
 */



/**
 * Initializes a new uintmod.
 *
 * @param bn The uintmod to initialize.
 * @return The newly initialized uintmod.
 */
uintmod_t* uintmod_init(uintmod_t* bn);



/**
 * Frees a uintmod.
 *
 * @param bn The uintmod to free.
 */
void uintmod_free(uintmod_t* bn);



/**
 * Prints the value of a uintmod in hex to a stream.
 *
 * @param out The stream to print to.
 * @param a The uintmod to print.
 *
 * @return The stream that was printed to.
 */
FILE* uintmod_print(FILE* out, const uintmod_t* a);



/**
 * Sets the size of a uintmod.
 *
 * @param a The uintmod to set the size of.
 * @param size The new size of the uintmod.
 *
 * @return The modified uintmod.
 */
uintmod_t* uintmod_set_size(uintmod_t* a, size_t size);



/**
 * Trims a uintmod to remove any redundant leading zeros.
 *
 * @param a The uintmod to trim.
 *
 * @return The trimmed uintmod.
 */
uintmod_t* uintmod_trim(uintmod_t* a);



/*
 * Setting
 */



/**
 * Sets the value of a uintmod by parsing hex input. The prefix "0x" is optional.
 *
 * @param a The uintmod to store the results in.
 * @param str The hex to parse.
 *
 * @return The uintmod from the hex.
 */
uintmod_t* uintmod_parse_hex(uintmod_t* a, const char* restrict str);



/**
 * Sets the value of a uintmod by parsing decimal input.
 *
 * @param a The uintmod to score the results in.
 * @param str The decimal to parse.
 * @return The uintmod from the decimal.
 */
uintmod_t* uintmod_parse_dec(uintmod_t* a, const char* restrict str);



/**
 * Sets the value of a uintmod to a uint32.
 *
 * @param a The uintmod to store the value in.
 * @param b The uint32 to use.
 *
 * @return The uintmod from the uint32.
 */
uintmod_t* uintmod_from_uint32(uintmod_t* a, uint32_t b);



/**
 * Computes a ← b.
 *
 * @param a The destination.
 * @param b The source.
 *
 * @return The copied value.
 */
uintmod_t* uintmod_copy(uintmod_t* a, const uintmod_t* b);



/*
 * Bitwise Operations
 */



/**
 * Computes r ← ~a.
 *
 * @param result The result of the operation.
 * @param a The value to invert.
 *
 * @return The result.
 */
uintmod_t* uintmod_not(uintmod_t* result, const uintmod_t* a);



/**
 * Computes r ← a & b.
 *
 * @param result The result of the operation.
 * @param a The first element.
 * @param b The second elements.
 *
 * @return The result.
 */
uintmod_t* uintmod_and(uintmod_t* result, const uintmod_t* a, const uintmod_t* b);



/**
 * Computes r ← ~(a & b).
 *
 * @param result The result of the operation.
 * @param a The first element.
 * @param b The second elements.
 *
 * @return The result.
 */
uintmod_t* uintmod_nand(uintmod_t* result, const uintmod_t* a, const uintmod_t* b);



/**
 * Computes r ← a | b.
 *
 * @param result The result of the operation.
 * @param a The first element.
 * @param b The second elements.
 *
 * @return The result.
 */
uintmod_t* uintmod_or(uintmod_t* result, const uintmod_t* a, const uintmod_t* b);



/**
 * Computes r ← a ^ b.
 *
 * @param result The result of the operation.
 * @param a The first element.
 * @param b The second elements.
 *
 * @return The result.
 */
uintmod_t* uintmod_xor(uintmod_t* result, const uintmod_t* a, const uintmod_t* b);



/**
 * Computes r ← ~(a | b).
 *
 * @param result The result of the operation.
 * @param a The first element.
 * @param b The second elements.
 *
 * @return The result.
 */
uintmod_t* uintmod_nor(uintmod_t* result, const uintmod_t* a, const uintmod_t* b);



/**
 * Computes r ← a << n.
 *
 * @param result The result of the operation.
 * @param a The value to shift.
 * @param bits The amount of bits to shift.
 *
 * @return The result.
 */
uintmod_t* uintmod_shift_left(uintmod_t* result, const uintmod_t* a, size_t bits);



/**
 * Computes r ← a >> n.
 *
 * @param result The result of the operation.
 * @param a The value to shift.
 * @param bits The amount of bits to shift.
 *
 * @return The result.
 */
uintmod_t* uintmod_shift_right(uintmod_t* result, const uintmod_t* a, size_t bits);



/**
 * Computes r ← a <<< b.
 *
 * @param result The result of the operation.
 * @param a The value to shift.
 * @param bits The amount of bits to shift.
 *
 * @return The result.
 */
uintmod_t* uintmod_rotate_left(uintmod_t* result, const uintmod_t* a, size_t bits);



/**
 * Computes r ← a >>> b.
 *
 * @param result The result of the operation.
 * @param a The value to shift.
 * @param bits The amount of bits to shift.
 *
 * @return The result.
 */
uintmod_t* uintmod_rotate_right(uintmod_t* result, const uintmod_t* a, size_t bits);



/**
 * Finds the most significant bit of a uintmod.
 *
 * @param a The value to evaluate.
 *
 * @return The index of the most significant bit.
 */
size_t uintmod_msb(const uintmod_t* a);



/**
 * Finds the least significant bit of a uintmod.
 *
 * @param a The value to evaluate.
 *
 * @return The index of the least significant bit.
 */
size_t uintmod_lsb(const uintmod_t* a);



/**
 * Gets the nth bit of a uintmod.
 *
 * @param a The value to evaluate.
 * @param index The index of the bit to get.
 *
 * @return The value of the bit.
 */
int uintmod_bitget(const uintmod_t* a, size_t index);



/**
 * Sets the nth bit of a uintmod.
 *
 * @param a The value to modify.
 * @param index The index of the bit to set.
 * @param value The new value of the bit.
 */
void uintmod_bitset(uintmod_t* a, size_t index, int value);



/**
 * Flips the nth bit of a uintmod.
 *
 * @param a The value to modify.
 * @param index The index of the bit to flip.
 */
void uintmod_bitflip(uintmod_t* a, size_t index);



/*
 * Logical Operations
 */



/**
 * Evaluates the equality of a = b.
 *
 * @param a The first value to compare.
 * @param b The second value to compare.
 *
 * @return True if the condition holds.
 */
bool uintmod_equal(const uintmod_t* a, const uintmod_t* b);



/**
 * Evaluates the inequality of a < b.
 *
 * @param a The first value to compare.
 * @param b The second value to compare.
 *
 * @return True if the condition holds.
 */
bool uintmod_lt(const uintmod_t* a, const uintmod_t* b);



/**
 * Evaluates the inequality of a > b.
 *
 * @param a The first value to compare.
 * @param b The second value to compare.
 *
 * @return True if the condition holds.
 */
bool uintmod_gt(const uintmod_t* a, const uintmod_t* b);



/**
 * Evaluates the inequality of a <= b.
 *
 * @param a The first value to compare.
 * @param b The second value to compare.
 *
 * @return True if the condition holds.
 */
bool uintmod_leq(const uintmod_t* a, const uintmod_t* b);



/**
 * Evaluates the inequality of a >= b.
 *
 * @param a The first value to compare.
 * @param b The second value to compare.
 *
 * @return True if the condition holds.
 */
bool uintmod_geq(const uintmod_t* a, const uintmod_t* b);



/*
 * Arithmetic Operations
 */



/**
 * Computes r ← a + b.
 *
 * @param result Where to store the result.
 * @param a The first value.
 * @param b The second value.
 *
 * @return The sum.
 */
uintmod_t* uintmod_add(uintmod_t* result, const uintmod_t* a, const uintmod_t* b);



/**
 * Computes r ← a - b.
 *
 * @param result Where to store the result.
 * @param a The first value.
 * @param b The second value.
 *
 * @return The difference.
 */
uintmod_t* uintmod_sub(uintmod_t* result, const uintmod_t* a, const uintmod_t* b);



/**
 * Computes r ← a / b.
 *
 * @param result Where to store the result.
 * @param a The dividend.
 * @param b The divisor.
 *
 * @return The quotient.
 */
uintmod_t* uintmod_div(uintmod_t* result, const uintmod_t* a, const uintmod_t* b);



/**
 * Computes r ← a * b.
 *
 * @param result Where to store the result.
 * @param a The first factor.
 * @param b The second factor.
 *
 * @return The product.
 */
uintmod_t* uintmod_mul(uintmod_t* result, const uintmod_t* a, const uintmod_t* b);



/**
 * Computes r ← exp(a, b).
 *
 * @param result Where to store the result.
 * @param a The base.
 * @param b The exponent.
 *
 * @return The power.
 */
uintmod_t* uintmod_pow(uintmod_t* result, const uintmod_t* a, const uintmod_t* b);



/**
 * Computes r ← a (mod b).
 *
 * @param result Where to store the result.
 * @param a The value.
 * @param b The moduli.
 *
 * @return The remainder.
 */
uintmod_t* uintmod_mod(uintmod_t* result, const uintmod_t* a, const uintmod_t* b);



#endif // MODNUMBER_H