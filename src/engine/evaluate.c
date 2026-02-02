#include <stddef.h>
#include <stdint.h>

#include "engine/evaluate.h"
#include "decision.h"
#include "error.h"

#include "rules/integrity.h"
#include "rules/device.h"
#include "rules/failures.h"

#include "audit/record.h"
#include "input/hash.h"

/* Forward declaration from audit/log.c */
int audit_log_append(
    RiskDecision decision,
    const uint8_t risk_input_hash[AUDIT_HASH_SIZE]
);

/* Ordered, mandatory rule list */
static RiskRuleFn RULES[] = {
    integrity_rule,
    device_rule,
    failure_rule
};

#define RULE_COUNT (sizeof(RULES) / sizeof(RULES[0]))

RiskDecision evaluate_risk(const RiskInput* input, uint32_t expected_hash)
{
    /* 1. Validate input (fail-closed) */
    if (validate_risk_input(input, expected_hash) != RISK_OK) {
        return RISK_DENY;
    }

    /* 2. Deterministic rule evaluation */
    RiskDecision decision = RISK_ALLOW;

    for (size_t i = 0; i < RULE_COUNT; i++) {
        RiskDecision r = RULES[i](input);

        if (r > decision) {
            decision = r;
        }

        if (decision == RISK_DENY) {
            break;
        }
    }

    /* 3. Compute canonical RiskInput hash */
    uint8_t input_hash[AUDIT_HASH_SIZE];

    if (compute_risk_input_hash(input, input_hash) != 0) {
        /* Hash failure = security failure */
        return RISK_DENY;
    }

    /* 4. Append audit log (mandatory, fail-secure) */
    if (audit_log_append(decision, input_hash) != 0) {
        /* No log → no decision */
        return RISK_DENY;
    }

    /* 5. Return decision */
    return decision;
}
