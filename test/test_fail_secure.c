#include <stdio.h>
#include <assert.h>

#include "engine/evaluate.h"
#include "input/validate.h"
#include "decision.h"

/* Case 1: NULL input */
/*
 * Verifies that passing a NULL input results in a DENY decision.
 */
static void test_null_input(void)
{
    RiskDecision d = evaluate_risk(NULL, 0);
    assert(d == RISK_DENY);
}

/* Case 2: Header missing */
/*
 * Verifies that an input with a missing header results in a DENY decision.
 */
static void test_missing_header(void)
{
    RiskInput input = {
        .header = NULL,
        .signals = NULL,
        .signal_count = 0
    };

    RiskDecision d = evaluate_risk(&input, 0);
    assert(d == RISK_DENY);
}

/* Case 3: Signal count mismatch */
/*
 * Verifies that a mismatch between declared signal count and actual signals is handled safely.
 */
static void test_invalid_signal_count(void)
{
    static RiskInputHeader header = {
        .schema_version = 1,
        .engine_version = 1,
        .signal_bitmap_hash = 0x12345678
    };

    RiskInput input = {
        .header = &header,
        .signals = NULL,   /* invalid */
        .signal_count = 2  /* claims signals exist */
    };

    RiskDecision d = evaluate_risk(&input, 0);
    assert(d == RISK_DENY);
}

/* Case 4: Invalid expected hash */
/*
 * Verifies that a mismatch in the expected signal bitmap hash results in a DENY decision.
 */
static void test_hash_mismatch(void)
{
    static RiskInputHeader header = {
        .schema_version = 1,
        .engine_version = 1,
        .signal_bitmap_hash = 0x99999999
    };

    RiskInput input = {
        .header = &header,
        .signals = NULL,
        .signal_count = 0
    };

    /* Pass a deliberately wrong expected hash */
    RiskDecision d = evaluate_risk(&input, 0xDEADBEEF);
    assert(d == RISK_DENY);
}

/*
 * Main entry point for fail-secure tests.
 * Runs a suite of negative test cases to ensure secure defaults.
 */
int main(void)
{
    test_null_input();
    test_missing_header();
    test_invalid_signal_count();
    test_hash_mismatch();

    printf("Fail-secure tests PASSED (all failures denied)\n");
    return 0;
}
