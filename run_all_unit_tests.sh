#!/bin/sh
set -e

CC=gcc
CFLAGS="-std=c11 -Iinclude -Itest"
UNITY_SRC="test/unity/unity.c"

echo "============================================================"
echo " RISK ENGINE – UNIT TEST EXECUTION (Unity)"
echo "============================================================"
echo

run_test () {
    NAME="$1"
    shift

    echo "------------------------------------------------------------"
    echo " TEST: $NAME"
    echo "------------------------------------------------------------"

    "$@"

    echo "------------------------------------------------------------"
    echo " RESULT: $NAME PASSED"
    echo "------------------------------------------------------------"
    echo
}

run_test "validate_risk_input" \
    $CC $CFLAGS \
    test/unit/test_validate_unit.c \
    $UNITY_SRC \
    src/input/validate.c \
    -o test_validate_unit.exe && \
    ./test_validate_unit.exe

run_test "normalize_signal" \
    $CC $CFLAGS \
    test/unit/test_normalize_unit.c \
    $UNITY_SRC \
    src/input/normalize.c \
    -o test_normalize_unit.exe && \
    ./test_normalize_unit.exe

run_test "compute_risk_input_hash" \
    $CC $CFLAGS \
    test/unit/test_hash_unit.c \
    $UNITY_SRC \
    src/input/hash.c \
    src/crypto/sha256.c \
    -o test_hash_unit.exe && \
    ./test_hash_unit.exe

run_test "sha256_core" \
    $CC $CFLAGS \
    test/unit/test_sha256_unit.c \
    $UNITY_SRC \
    src/crypto/sha256.c \
    -o test_sha256_unit.exe && \
    ./test_sha256_unit.exe

run_test "failure_rule" \
    $CC $CFLAGS \
    test/unit/test_rules_failures_unit.c \
    $UNITY_SRC \
    src/rules/failures.c \
    -o test_rules_failures_unit.exe && \
    ./test_rules_failures_unit.exe

run_test "integrity_rule" \
    $CC $CFLAGS \
    test/unit/test_rules_integrity_unit.c \
    $UNITY_SRC \
    src/rules/integrity.c \
    -o test_rules_integrity_unit.exe && \
    ./test_rules_integrity_unit.exe

run_test "device_rule" \
    $CC $CFLAGS \
    test/unit/test_rules_device_unit.c \
    $UNITY_SRC \
    src/rules/device.c \
    -o test_rules_device_unit.exe && \
    ./test_rules_device_unit.exe

echo "============================================================"
echo " ALL UNIT TESTS PASSED ✅"
echo "============================================================"
