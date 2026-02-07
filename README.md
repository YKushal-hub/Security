# Risk Engine - Security Risk Assessment Library

A deterministic, fail-closed security decision engine implemented in C11 for evaluating authentication and authorization risk.

## Features

- 🛡️ **Fail-Closed Architecture** - Secure by default, ensuring any failure results in a safe deny state
- ⚡ **Deterministic Evaluation** - Guaranteed consistent outcomes through strictly ordered rule evaluation (Integrity → Device → Failures)
- 📝 **Immutable Audit Logging** - Cryptographically verifiable audit trails using SHA-256 input binding
- 🚀 **High Performance** - Zero dynamic memory allocation on the evaluation hot path
- 🧩 **Modular Rule Design** - Extensible architecture for adding new risk signals
- ✅ **Strict Input Validation** - Comprehensive schema validation and normalization before processing

## Tech Stack

- **C11** - Core implementation language
- **GNU Make** - Build system
- **GCC / Clang** - Supported compilers
- **Standard C Library** - Zero external dependencies
- **SHA-256** - Cryptographic operations for integrity and logging
- **Bash** - Test automation scripts

## Getting Started

### Prerequisites

- GCC or Clang compiler
- GNU Make
- Bash (for running test scripts)

### Installation

1. **Clone the repository:**
```bash
git clone https://github.com/yourusername/risk-engine.git
cd Security
```

2. **Build the project:**
```bash
make
```

This will produce the `risk_engine.o` object file ready for linking.

### Development

**Run all unit tests:**
```bash
./run_all_unit_tests.sh
```

**Clean build artifacts:**
```bash
make clean
```

### Integration

To integrate the Risk Engine into your application, link against `risk_engine.o` and include the public headers.

```c
#include "engine/evaluate.h"
#include "decision.h"

// Example usage
RiskInput input = { /* populate risk signals */ };
uint32_t expected_hash = 0x12345678;
RiskDecision decision = evaluate_risk(&input, expected_hash);

if (decision == RISK_ALLOW) {
    // Grant access
} else {
    // Deny or step-up authentication
}
```

## Project Structure

```
Security/
├── include/              # Public API headers
│   ├── decision.h        # Risk decision enums
│   ├── error.h           # Error codes
│   └── version.h         # Version information
├── src/                  # Source code
│   ├── engine/           # Core evaluation pipeline
│   ├── rules/            # Risk rule logic (integrity, device, failures)
│   ├── input/            # Input validation & normalization
│   ├── audit/            # Audit logging mechanisms
│   └── crypto/           # SHA-256 implementation
├── test/                 # Unit and integration tests
├── Makefile              # Build configuration
├── run_all_unit_tests.sh # Test runner script
└── README.md             # This file
```

## Core Components

- **RiskInput** - Struct capturing all security context (IP, Device ID, User History)
- **RiskDecision** - Enum representing the evaluation outcome (ALLOW, STEP_UP, DENY)
- **Rules** - Modular logic units:
    - **Integrity Rule**: Verifies data tamper resistance
    - **Device Rule**: Validates device trust signals
    - **Failures Rule**: Checks history of recent failures

## Security Features

- ✅ **Fail-Closed Logic**: Any internal error or validation failure defaults to DENY
- ✅ **Memory Safety**: No `malloc` usage during request processing preventing heap fragmentation and leaks
- ✅ **Input Sanitization**: Strict validation of all input fields against defined schemas
- ✅ **Canonicalization**: Inputs are normalized before hashing to ensure consistent signatures
- ✅ **Compiler Hardening**: Built with `-fno-builtin`, `-Werror`, and stack protection flags


## License

MIT
