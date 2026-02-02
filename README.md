Security Risk Engine
A high-performance codebase designed to evaluate security signals and enforce risk decisions (ALLOW, STEP_UP, DENY).

This engine is built for reliability, determinism, and auditability, making it suitable for critical authentication and authorization flows where failure is not an option.

🚀 Features
The Security Risk Engine is architected with a specific focus on safety and speed:

🛡️ Fail-Closed Architecture The engine defaults to a safe state (DENY) upon any validation failure, schema mismatch, or internal error.

⚡ Deterministic Evaluation Rules are applied in a strict, predictable order:

Integrity Checks

Device Signals

Failure History

📝 Immutable Audit Logging Every decision is cryptographically bound to the input via SHA-256 hashing, ensuring the log cannot be tampered with without detection.

🧩 Modular Design Easily extensible architecture allows for adding new risk signals and evaluation rules without rewriting the core logic.

🏎️ High Performance Written in C11 with zero runtime dependencies (Standard C Library only) and no dynamic memory allocation on the hot path.

🛠️ Tech Stack
Language: C11

Build System: Make

Compiler: GCC (recommended), Clang compatible

Dependencies: None (Standard C Library only)

📂 Project Structure
Plaintext
Security/
├── include/              # Public header files exposing the API
│   ├── decision.h        # Risk decision enum definitions
│   └── ...
├── src/                  # Source code implementation
│   ├── engine/           # Core evaluation logic
│   ├── rules/            # Specific risk rule implementations
│   ├── input/            # Input validation and sanitization
│   ├── audit/            # Audit logging and record keeping
│   └── crypto/           # Cryptographic primitives (SHA-256)
├── test/                 # Unit and integration tests
├── Makefile              # Build configuration
└── README.md             # Project documentation
⚙️ Installation
Ensure you have gcc and make installed on your system.

1. Clone the repository

Bash
git clone https://github.com/yourusername/security-risk-engine.git
cd security-risk-engine
2. Build the project This will produce the risk_engine.o object file ready for linking.

Bash
make
3. Clean build artifacts (Optional)

Bash
make clean
💻 Usage
Integrate the engine into your application by including the header and linking the object file.

C API Example
C
#include "engine/evaluate.h"
#include "decision.h"
#include <stdint.h>

int main() {
    // 1. Prepare your input data
    // Ensure struct matches schema version defined in headers
    RiskInput input = { /* ... populate signals ... */ };
    
    // Hash provided by the trusted caller/source for integrity verification
    uint32_t expected_hash = 0x12345678; 

    // 2. Evaluate risk
    RiskDecision decision = evaluate_risk(&input, expected_hash);

    // 3. Act on decision
    switch (decision) {
        case RISK_ALLOW:
            // Grant access
            break;
            
        case RISK_STEP_UP:
            // Challenge user (MFA, Email OTP, etc.)
            break;
            
        case RISK_DENY:
        default:
            // FAIL-SAFE: Deny access and alert
            break;
    }
    
    return 0;
}
🔒 Security Considerations
Because this engine protects critical paths, several security guarantees are enforced:

Input Validation: The usage of validate.c ensures all inputs conform to schema versions and structural integrity before processing begins.

Memory Safety: The core engine avoids dynamic memory allocation (malloc/free) on the hot path. This prevents heap fragmentation, memory leaks, and Out-Of-Memory (OOM) crashes during high load.

Canonical Hashing: All inputs are hashed using SHA-256 to ensure the audit log matches exactly what was evaluated, preventing "check-of-time vs use-of-time" discrepancies.
