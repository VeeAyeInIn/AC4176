#ifndef BIGNUMBER_H
#define BIGNUMBER_H



#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>



/*
 * Data Structures
 */



/**
 * A data-type similar to uints from `stdint.h`. A uintx stores an unspecified amount of data, in the form of uint32s.
 */
typedef struct uintx {
    uint32_t* data;
    size_t size;
} uintx_t;



/*
 * Constants Getters
 */



const uintx_t* uintx_zero(void);



const uintx_t* uintx_one(void);



/*
 * Memory
 */



/**
 * Initializes a new uintx.
 *
 * @param bn The uintx to initialize.
 * @return The newly initialized uintx.
 */
uintx_t* uintx_init(uintx_t* bn);



/**
 * Frees a uintx.
 *
 * @param bn The uintx to free.
 */
void uintx_free(uintx_t* bn);



/**
 * Prints the value of a uintx in hex to a stream.
 *
 * @param out The stream to print to.
 * @param a The uintx to print.
 *
 * @return The stream that was printed to.
 */
FILE* uintx_print(FILE* out, const uintx_t* a);



/**
 * Sets the size of a uintx.
 *
 * @param a The uintx to set the size of.
 * @param size The new size of the uintx.
 *
 * @return The modified uintx.
 */
uintx_t* uintx_set_size(uintx_t* a, size_t size);



/**
 * Trims a uintx to remove any redundant leading zeros.
 *
 * @param a The uintx to trim.
 *
 * @return The trimmed uintx.
 */
uintx_t* uintx_trim(uintx_t* a);



/*
 * Setting
 */



/**
 * Sets the value of a uintx by parsing hex input. The prefix "0x" is optional.
 *
 * @param a The uintx to store the results in.
 * @param str The hex to parse.
 *
 * @return The uintx from the hex.
 */
uintx_t* uintx_parse_hex(uintx_t* a, const char* restrict str);



/**
 * Sets the value of a uintx by parsing decimal input.
 *
 * @param a The uintx to score the results in.
 * @param str The decimal to parse.
 * @return The uintx from the decimal.
 */
uintx_t* uintx_parse_dec(uintx_t* a, const char* restrict str);



/**
 * Sets the value of a uintx to a uint32.
 *
 * @param a The uintx to store the value in.
 * @param b The uint32 to use.
 *
 * @return The uintx from the uint32.
 */
uintx_t* uintx_from_uint32(uintx_t* a, uint32_t b);



/**
 * Computes a ← b.
 *
 * @param a The destination.
 * @param b The source.
 *
 * @return The copied value.
 */
uintx_t* uintx_copy(uintx_t* a, const uintx_t* b);



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
uintx_t* uintx_not(uintx_t* result, const uintx_t* a);



/**
 * Computes r ← a & b.
 *
 * @param result The result of the operation.
 * @param a The first element.
 * @param b The second elements.
 *
 * @return The result.
 */
uintx_t* uintx_and(uintx_t* result, const uintx_t* a, const uintx_t* b);



/**
 * Computes r ← ~(a & b).
 *
 * @param result The result of the operation.
 * @param a The first element.
 * @param b The second elements.
 *
 * @return The result.
 */
uintx_t* uintx_nand(uintx_t* result, const uintx_t* a, const uintx_t* b);



/**
 * Computes r ← a | b.
 *
 * @param result The result of the operation.
 * @param a The first element.
 * @param b The second elements.
 *
 * @return The result.
 */
uintx_t* uintx_or(uintx_t* result, const uintx_t* a, const uintx_t* b);



/**
 * Computes r ← a ^ b.
 *
 * @param result The result of the operation.
 * @param a The first element.
 * @param b The second elements.
 *
 * @return The result.
 */
uintx_t* uintx_xor(uintx_t* result, const uintx_t* a, const uintx_t* b);



/**
 * Computes r ← ~(a | b).
 *
 * @param result The result of the operation.
 * @param a The first element.
 * @param b The second elements.
 *
 * @return The result.
 */
uintx_t* uintx_nor(uintx_t* result, const uintx_t* a, const uintx_t* b);



/**
 * Computes r ← a << n.
 *
 * @param result The result of the operation.
 * @param a The value to shift.
 * @param bits The amount of bits to shift.
 *
 * @return The result.
 */
uintx_t* uintx_shift_left(uintx_t* result, const uintx_t* a, size_t bits);



/**
 * Computes r ← a >> n.
 *
 * @param result The result of the operation.
 * @param a The value to shift.
 * @param bits The amount of bits to shift.
 *
 * @return The result.
 */
uintx_t* uintx_shift_right(uintx_t* result, const uintx_t* a, size_t bits);



/**
 * Computes r ← a <<< b.
 *
 * @param result The result of the operation.
 * @param a The value to shift.
 * @param bits The amount of bits to shift.
 *
 * @return The result.
 */
uintx_t* uintx_rotate_left(uintx_t* result, const uintx_t* a, size_t bits);



/**
 * Computes r ← a >>> b.
 *
 * @param result The result of the operation.
 * @param a The value to shift.
 * @param bits The amount of bits to shift.
 *
 * @return The result.
 */
uintx_t* uintx_rotate_right(uintx_t* result, const uintx_t* a, size_t bits);



/**
 * Finds the most significant bit of a uintx.
 *
 * @param a The value to evaluate.
 *
 * @return The index of the most significant bit.
 */
size_t uintx_msb(const uintx_t* a);



/**
 * Finds the least significant bit of a uintx.
 *
 * @param a The value to evaluate.
 *
 * @return The index of the least significant bit.
 */
size_t uintx_lsb(const uintx_t* a);



/**
 * Gets the nth bit of a uintx.
 *
 * @param a The value to evaluate.
 * @param index The index of the bit to get.
 *
 * @return The value of the bit.
 */
int uintx_bitget(const uintx_t* a, size_t index);



/**
 * Sets the nth bit of a uintx.
 *
 * @param a The value to modify.
 * @param index The index of the bit to set.
 * @param value The new value of the bit.
 */
void uintx_bitset(uintx_t* a, size_t index, int value);



/**
 * Flips the nth bit of a uintx.
 *
 * @param a The value to modify.
 * @param index The index of the bit to flip.
 */
void uintx_bitflip(uintx_t* a, size_t index);



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
bool uintx_equal(const uintx_t* a, const uintx_t* b);



/**
 * Evaluates the inequality of a < b.
 *
 * @param a The first value to compare.
 * @param b The second value to compare.
 *
 * @return True if the condition holds.
 */
bool uintx_lt(const uintx_t* a, const uintx_t* b);



/**
 * Evaluates the inequality of a > b.
 *
 * @param a The first value to compare.
 * @param b The second value to compare.
 *
 * @return True if the condition holds.
 */
bool uintx_gt(const uintx_t* a, const uintx_t* b);



/**
 * Evaluates the inequality of a <= b.
 *
 * @param a The first value to compare.
 * @param b The second value to compare.
 *
 * @return True if the condition holds.
 */
bool uintx_leq(const uintx_t* a, const uintx_t* b);



/**
 * Evaluates the inequality of a >= b.
 *
 * @param a The first value to compare.
 * @param b The second value to compare.
 *
 * @return True if the condition holds.
 */
bool uintx_geq(const uintx_t* a, const uintx_t* b);



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
uintx_t* uintx_add(uintx_t* result, const uintx_t* a, const uintx_t* b);



/**
 * Computes r ← a - b.
 *
 * @param result Where to store the result.
 * @param a The first value.
 * @param b The second value.
 *
 * @return The difference.
 */
uintx_t* uintx_sub(uintx_t* result, const uintx_t* a, const uintx_t* b);



/**
 * Computes r ← a / b.
 *
 * @param result Where to store the result.
 * @param a The dividend.
 * @param b The divisor.
 *
 * @return The quotient.
 */
uintx_t* uintx_div(uintx_t* result, const uintx_t* a, const uintx_t* b);



/**
 * Computes r ← a * b.
 *
 * @param result Where to store the result.
 * @param a The first factor.
 * @param b The second factor.
 *
 * @return The product.
 */
uintx_t* uintx_mul(uintx_t* result, const uintx_t* a, const uintx_t* b);



/**
 * Computes r ← exp(a, b).
 *
 * @param result Where to store the result.
 * @param a The base.
 * @param b The exponent.
 *
 * @return The power.
 */
uintx_t* uintx_pow(uintx_t* result, const uintx_t* a, const uintx_t* b);



/**
 * Computes r ← a (mod b).
 *
 * @param result Where to store the result.
 * @param a The value.
 * @param b The moduli.
 *
 * @return The remainder.
 */
uintx_t* uintx_mod(uintx_t* result, const uintx_t* a, const uintx_t* b);



uintx_t* uintx_sqmul(uintx_t* result, const uintx_t* a, const uintx_t* b, const uintx_t* m);



#endif // BIGNUMBER_H