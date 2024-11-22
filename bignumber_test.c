#include "../Unity/src/unity.h"
#include "../src/bignumber.h"
#include "_test_util.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>



/*
 * This section is for any variables that will be used in testing.
 */



uintx_t zero;
uintx_t one;
uintx_t two;

uintx_t uintx1;
uintx_t uintx2;
uintx_t uintx3;
uintx_t uintx4;
uintx_t uintx5;
uintx_t uintx6;
uintx_t uintx7;
uintx_t uintx8;
uintx_t uintx9;



// static size_t lazy_pread(uint4096_t* a, char* buffer, FILE* fp) {
//     bn_print(a, fp);
//     return pread(buffer, fp);
// }



/*
 * This section is for setting up the big numbers, as well as tearing them down, which is used to initialize and reset
 * them between tests.
 */



void setUp(void) {

    uintx_init(&zero);
    uintx_parse_hex(&zero, "0x0");

    uintx_init(&one);
    uintx_parse_hex(&one, "0x1");

    uintx_init(&two);
    uintx_parse_hex(&two, "0x2");

    uintx_init(&uintx1);
    uintx_parse_hex(&uintx1, "0x12345678");

    uintx_init(&uintx2);
    uintx_parse_hex(&uintx2, "0x1234567890ABCDEF");

    uintx_init(&uintx3);
    uintx_parse_hex(&uintx3, "00000009");

    uintx_init(&uintx4);
    uintx_parse_hex(&uintx4, "1234567");

    uintx_init(&uintx5);
    uintx_parse_hex(&uintx5, "123456789");

    uintx_init(&uintx6);
    uintx_parse_hex(&uintx6, "123456789");

    uintx_init(&uintx7);
    uintx_parse_hex(&uintx7, "123456789");

    uintx_init(&uintx8);
    uintx_parse_hex(&uintx8, "123456789");

    uintx_init(&uintx9);
    uintx_parse_hex(&uintx9, "123");

}



void tearDown(void) {

    uintx_free(&zero);
    uintx_free(&one);
    uintx_free(&uintx1);
    uintx_free(&uintx2);
    uintx_free(&uintx3);
    uintx_free(&uintx4);
    uintx_free(&uintx5);

}



/*
 * Memory
 */



void test_init(void) {

    uintx_t uintx_test = { NULL, 0 };

    // Check for expected values before initialization.
    TEST_ASSERT_NULL_MESSAGE(uintx_test.data, "Expected data to be NULL.");
    TEST_ASSERT_EQUAL_MESSAGE(0, uintx_test.size, "Expected size to be 0.");

    uintx_init(&uintx_test);

    // Check for expected values after initialization.
    TEST_ASSERT_NOT_NULL_MESSAGE(uintx_test.data, "Expected data to not be NULL.");
    TEST_ASSERT_EQUAL_MESSAGE(1, uintx_test.size, "Expected size to be 1.");

    uintx_free(&uintx_test);

}



void test_free(void) {

    uint32_t* value = calloc(1, sizeof(uint32_t));
    *value = 123;

    uintx_t uintx_test = { value, 1 };

    // Check for expected values before free.
    TEST_ASSERT_EQUAL_PTR_MESSAGE(value, uintx_test.data, "Expected data pointer to match value.");
    TEST_ASSERT_EQUAL_MESSAGE(1, uintx_test.size, "Expected size to be 1.");

    uintx_free(&uintx_test);

    // Check for expected values after free.
    TEST_ASSERT_NULL_MESSAGE(uintx_test.data, "Expected data to be NULL.");
    TEST_ASSERT_EQUAL_MESSAGE(0, uintx_test.size, "Expected size to be 0.");

    uintx_free(&uintx_test);

}



/*
 * Setting
 */



void test_parse_hex(void) {

    uintx_t uintx_test;
    uintx_init(&uintx_test);

    uintx_parse_hex(&uintx_test, "0x123");
    TEST_ASSERT_EQUAL_MESSAGE(0x123, uintx_test.data[0], "Expected data[0] to be 0x123.");
    TEST_ASSERT_EQUAL_MESSAGE(1, uintx_test.size, "Expected size to be 1.");

    uintx_parse_hex(&uintx_test, "");
    TEST_ASSERT_EQUAL_MESSAGE(0, uintx_test.data[0], "Expected data[0] to be 0x0.");
    TEST_ASSERT_EQUAL_MESSAGE(1, uintx_test.size, "Expected size to be 1.");

    uintx_parse_hex(&uintx_test, "00000123");
    TEST_ASSERT_EQUAL_MESSAGE(0x123, uintx_test.data[0], "Expected data[0] to be 0x123.");
    TEST_ASSERT_EQUAL_MESSAGE(1, uintx_test.size, "Expected size to be 1.");

    uintx_parse_hex(&uintx_test, "000000123");
    TEST_ASSERT_EQUAL_MESSAGE(0x123, uintx_test.data[0], "Expected data[0] to be 0x123.");
    TEST_ASSERT_EQUAL_MESSAGE(1, uintx_test.size, "Expected size to be 1.");

    uintx_parse_hex(&uintx_test, "12345678");
    TEST_ASSERT_EQUAL_MESSAGE(0x12345678, uintx_test.data[0], "Expected data[0] to be 0x12345678.");
    TEST_ASSERT_EQUAL_MESSAGE(1, uintx_test.size, "Expected size to be 1.");

    uintx_parse_hex(&uintx_test, "0x1234567890ABCDEF");
    TEST_ASSERT_EQUAL_MESSAGE(0x12345678, uintx_test.data[0], "Expected data[0] to be 0x12345678.");
    TEST_ASSERT_EQUAL_MESSAGE(0x90ABCDEF, uintx_test.data[1], "Expected data[1] to be 0x90ABCDEF.");
    TEST_ASSERT_EQUAL_MESSAGE(2, uintx_test.size, "Expected size to be 2.");

    uintx_free(&uintx_test);

}



/*
 * Bitwise Operations
 */



void test_msb(void) {

    uintx_t uintx_test;
    uintx_init(&uintx_test);

    uintx_parse_hex(&uintx_test, "0x1");
    TEST_ASSERT_EQUAL_MESSAGE(0, uintx_msb(&uintx_test), "Expected msb to be at index 0.");

    uintx_parse_hex(&uintx_test, "0x2");
    TEST_ASSERT_EQUAL_MESSAGE(1, uintx_msb(&uintx_test), "Expected msb to be at index 1.");

    uintx_parse_hex(&uintx_test, "0x4");
    TEST_ASSERT_EQUAL_MESSAGE(2, uintx_msb(&uintx_test), "Expected msb to be at index 2.");

    uintx_parse_hex(&uintx_test, "0x11");
    TEST_ASSERT_EQUAL_MESSAGE(4, uintx_msb(&uintx_test), "Expected msb to be at index 4.");

    uintx_parse_hex(&uintx_test, "0x123456781");
    TEST_ASSERT_EQUAL_MESSAGE(32, uintx_msb(&uintx_test), "Expected msb to be at index 32.");

    uintx_free(&uintx_test);

}



void test_bitget(void) {

    uintx_t uintx_test;
    uintx_init(&uintx_test);
    uintx_parse_hex(&uintx_test, "0x12345678"); // Binary: 0001 0010 0011 0100 0101 0110 0111 1000

    // Test individual bits
    TEST_ASSERT_EQUAL_MESSAGE(0, uintx_bitget(&uintx_test, 0), "Bit 0 should be 0.");
    TEST_ASSERT_EQUAL_MESSAGE(0, uintx_bitget(&uintx_test, 1), "Bit 1 should be 0.");
    TEST_ASSERT_EQUAL_MESSAGE(0, uintx_bitget(&uintx_test, 2), "Bit 2 should be 0.");
    TEST_ASSERT_EQUAL_MESSAGE(1, uintx_bitget(&uintx_test, 3), "Bit 3 should be 1.");
    TEST_ASSERT_EQUAL_MESSAGE(1, uintx_bitget(&uintx_test, 28), "Bit 28 should be 1.");
    TEST_ASSERT_EQUAL_MESSAGE(0, uintx_bitget(&uintx_test, 29), "Bit 29 should be 0.");
    TEST_ASSERT_EQUAL_MESSAGE(0, uintx_bitget(&uintx_test, 30), "Bit 30 should be 0.");
    TEST_ASSERT_EQUAL_MESSAGE(0, uintx_bitget(&uintx_test, 31), "Bit 31 should be 0.");

    uintx_free(&uintx_test);

}



/*
 * Logical Operations
 */



/*
 * Arithmetic Operations
 */



void test_add(void) {

    uintx_t result;
    uintx_init(&result);

    // Test the additive identity.
    uintx_add(&result, &uintx1, &zero);
    TEST_ASSERT_EQUAL_MESSAGE(0x12345678, result.data[0], "Expected data[0] to be 0x12345678.");
    TEST_ASSERT_EQUAL_MESSAGE(1, result.size, "Expected size to be 1.");

    // Test the additive identity.
    uintx_add(&result, &uintx2, &zero);
    TEST_ASSERT_EQUAL_MESSAGE(0x12345678, result.data[0], "Expected data[0] to be 0x12345678.");;
    TEST_ASSERT_EQUAL_MESSAGE(0x90ABCDEF, result.data[1], "Expected data[0] to be 0x90ABCDEF.");
    TEST_ASSERT_EQUAL_MESSAGE(2, result.size, "Expected size to be 2.");

    uintx_free(&result);

}



void test_div(void) {

    uintx_t a;
    uintx_t b;
    uintx_t quotient;

    uintx_init(&a);
    uintx_init(&b);
    uintx_init(&quotient);

    uintx_parse_hex(&a, "0x2");
    uintx_parse_hex(&b, "0x1");

    uintx_div(&quotient, &a, &b);

    TEST_ASSERT_EQUAL_MESSAGE(0x2, quotient.data[0], "Expected quotient to be 0x2.");
    TEST_ASSERT_EQUAL_MESSAGE(1, quotient.size, "Expected size to be 1.");

    uintx_free(&a);
    uintx_free(&b);
    uintx_free(&quotient);

}



void test_mul(void) {

    uintx_t result;
    uintx_init(&result);

    // Test the multiplicative identity.
    uintx_mul(&result, &uintx1, &one);
    TEST_ASSERT_EQUAL_MESSAGE(0x12345678, result.data[0], "Expected data[0] to be 0x12345678.");
    TEST_ASSERT_EQUAL_MESSAGE(1, result.size, "Expected size to be 1.");

    // Test the multiplicative identity.
    uintx_mul(&result, &uintx2, &one);
    TEST_ASSERT_EQUAL_MESSAGE(0x12345678, result.data[0], "Expected data[0] to be 0x12345678.");;
    TEST_ASSERT_EQUAL_MESSAGE(0x90ABCDEF, result.data[1], "Expected data[0] to be 0x90ABCDEF.");
    TEST_ASSERT_EQUAL_MESSAGE(2, result.size, "Expected size to be 2.");

    uintx_mul(&result, &uintx9, &uintx9);
    TEST_ASSERT_EQUAL_MESSAGE(0x14AC9, result.data[0], "Expected data[0] to be 0x14AC9.");
    TEST_ASSERT_EQUAL_MESSAGE(1, result.size, "Expected size to be 1.");

    uintx_free(&result);

}



void test_pow(void) {

    uintx_t result;
    uintx_init(&result);

    uintx_pow(&result, &uintx9, &one);
    TEST_ASSERT_EQUAL_MESSAGE(0x123, result.data[0], "Expected data[0] to be 0x123.");
    TEST_ASSERT_EQUAL_MESSAGE(1, result.size, "Expected size to be 1.");

    uintx_pow(&result, &uintx9, &two);
    TEST_ASSERT_EQUAL_MESSAGE(0x14AC9, result.data[0], "Expected data[0] to be 0x14AC9.");
    TEST_ASSERT_EQUAL_MESSAGE(1, result.size, "Expected size to be 1.");

    uintx_pow(&result, &uintx1, &two);
    TEST_ASSERT_EQUAL_MESSAGE(0x1DF4D840, result.data[0], "Expected data[0] to be 0x1DF4D840.");
    TEST_ASSERT_EQUAL_MESSAGE(0x14B66DC, result.data[1], "Expected data[1] to be 0x14B66DC.");

    uintx_pow(&result, &uintx9, &uintx9);

    uintx_free(&result);

}



/*
 * The main method to run the tests.
 */



// not needed when using generate_test_runner.rb
int main(void) {

    UNITY_BEGIN();

    RUN_TEST(test_init);
    RUN_TEST(test_free);

    RUN_TEST(test_parse_hex);

    RUN_TEST(test_msb);
    RUN_TEST(test_bitget);

    RUN_TEST(test_add);
    RUN_TEST(test_div);
    RUN_TEST(test_mul);
    RUN_TEST(test_pow);

    return UNITY_END();

}