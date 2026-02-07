#!/bin/sh
set -e

echo "========================================"
echo " Running ALL UNIT TESTS (Unity)"
echo " Project: risk-engine"
echo "========================================"
echo

# Compiler and flags
CC=gcc
CFLAGS="-std=c11 -Iinclude -Itest"

UNITY_SRC="test/unity/unity.c"

echo "[1/7] validate_risk_input unit test"
$CC $CFLAGS \
    test/unit/test_validate_unit.c \
    $UNITY_SRC \
    src/input/validate.c \
    -o test_validate_unit.exe
./test_validate_unit.exe
echo

echo "[2/7] normalize_signal unit test"
$CC $CFLAGS \
    test/unit/test_normalize_unit.c \
    $UNITY_SRC \
    src/input/normalize.c \
    -o test_normalize_unit.exe
./test_normalize_unit.exe
echo

echo "[3/7] compute_risk_input_hash unit test"
$CC $CFLAGS \
    test/unit/test_hash_unit.c \
    $UNITY_SRC \
    src/input/hash.c \
    src/crypto/sha256.c \
    -o test_hash_unit.exe
./test_hash_unit.exe
echo

echo "[4/7] SHA-256 unit test"
$CC $CFLAGS \
    test/unit/test_sha256_unit.c \
    $UNITY_SRC \
    src/crypto/sha256.c \
    -o test_sha256_unit.exe
./test_sha256_unit.exe
echo

echo "[5/7] failure_rule unit test"
$CC $CFLAGS \
    test/unit/test_rules_failures_unit.c \
    $UNITY_SRC \
    src/rules/failures.c \
    -o test_rules_failures_unit.exe
./test_rules_failures_unit.exe
echo

echo "[6/7] integrity_rule unit test"
$CC $CFLAGS \
    test/unit/test_rules_integrity_unit.c \
    $UNITY_SRC \
    src/rules/integrity.c \
    -o test_rules_integrity_unit.exe
./test_rules_integrity_unit.exe
echo

echo "[7/7] device_rule unit test"
$CC $CFLAGS \
    test/unit/test_rules_device_unit.c \
    $UNITY_SRC \
    src/rules/device.c \
    -o test_rules_device_unit.exe
./test_rules_device_unit.exe
echo

echo "========================================"
echo " ALL UNIT TESTS PASSED ✅"
echo "========================================"
