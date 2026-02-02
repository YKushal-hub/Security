Security Risk Engine

A deterministic, fail-closed security decision engine implemented in C11 for evaluating authentication and authorization risk.
The engine consumes validated security signals and produces one of three decisions: ALLOW, STEP_UP, or DENY.

This project is designed for critical security paths where correctness, predictability, and auditability are more important than convenience or dynamic flexibility.

🔐 Problem Statement

Modern authentication systems rely on multiple security signals (device trust, integrity checks, failure history).
If these signals are evaluated inconsistently or fail open under error conditions, attackers can exploit the system.

This engine addresses that risk by enforcing:

Fail-closed behavior

Strict evaluation order

Cryptographically verifiable audit logs

🚀 Key Features

🛡️ Fail-Closed Architecture

Any validation failure, malformed input, or internal error results in a DENY decision.

Prevents privilege escalation caused by partial or corrupted data.

⚡ Deterministic Rule Evaluation

Rules are evaluated in a fixed, predefined order:

Integrity → Device Trust → Failure History

Guarantees reproducible outcomes for identical inputs.

📝 Immutable Audit Logging

Every evaluation is bound to a SHA-256 hash of canonicalized input.

Enables post-incident verification and tamper detection.

🧩 Modular Rule Design

Risk signals and rules are logically separated.

New rules can be added without altering the evaluation contract.

🏎️ High-Performance, Low-Level Implementation

Written in C11

No runtime dependencies

No dynamic allocation on the hot path

🛠️ Technology Stack
Component	Choice
Language	C (C11 standard)
Build System	Make
Compiler	GCC (recommended), Clang compatible
Dependencies	None (Standard C Library only)


📂 Project Structure
Security/
├── include/              # Public API headers
│   ├── decision.h        # Risk decision enums
│   └── ...
├── src/
│   ├── engine/           # Core evaluation pipeline
│   ├── rules/            # Individual risk rule logic
│   ├── input/            # Input validation & sanitization
│   ├── audit/            # Audit logging mechanisms
│   └── crypto/           # SHA-256 implementation
├── test/                 # Unit and integration tests
├── Makefile              # Build configuration
└── README.md             # Documentation

⚙️ Build & Installation
Prerequisites

GCC or Clang

GNU Make

Build
make


This produces:

risk_engine.o


which can be statically or dynamically linked into your application.

Clean
make clean

💻 Usage Example
API Integration (C)
#include "engine/evaluate.h"
#include "decision.h"

int main() {
    RiskInput input = {
        /* populate validated security signals */
    };

    uint32_t expected_hash = 0x12345678; // Obtained from a trusted source

    RiskDecision decision = evaluate_risk(&input, expected_hash);

    switch (decision) {
        case RISK_ALLOW:
            // Grant access
            break;

        case RISK_STEP_UP:
            // Trigger MFA / secondary verification
            break;

        case RISK_DENY:
        default:
            // Deny access and log incident
            break;
    }

    return 0;
}

🔒 Security Design Considerations

Input Validation

All inputs are validated against expected schemas before evaluation.

Invalid or unexpected fields immediately terminate processing.

Memory Safety

No dynamic memory allocation during evaluation.

Reduces attack surface related to heap corruption and memory leaks.

Canonical Hashing

Inputs are normalized before hashing.

Ensures audit logs match exactly what was evaluated.

Fail-Fast Error Handling

Errors are surfaced immediately and mapped to DENY.

Prevents undefined behavior from propagating into decisions.

🧠 Design Rationale
Design Choice	Reason
C11	Predictable performance, no runtime overhead
Fail-Closed	Security systems must default to denial
Determinism	Required for auditing and incident response
No Dependencies	Reduces supply-chain and runtime risk
