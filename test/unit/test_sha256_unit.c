#include "unity/unity.h"
#include "crypto/sha256.h"
#include <string.h>

/*
 * Unity setup stub.
 */
void setUp(void) {}
/*
 * Unity teardown stub.
 */
void tearDown(void) {}

/*
 * Verifies that the SHA-256 implementation is consistent and reproducible.
 */
void test_sha256_consistency(void)
{
    const uint8_t data[] = "abc";
    uint8_t h1[32], h2[32];

    Sha256Ctx c1, c2;

    sha256_init(&c1);
    sha256_update(&c1, data, 3);
    sha256_final(&c1, h1);

    sha256_init(&c2);
    sha256_update(&c2, data, 3);
    sha256_final(&c2, h2);

    TEST_ASSERT_EQUAL_MEMORY(h1, h2, 32);
}

/*
 * Main entry point for SHA-256 unit tests.
 */
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_sha256_consistency);
    return UNITY_END();
}
