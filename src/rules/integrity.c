#include "rules/integrity.h"

/*
 * Evaluates risk based on the secure boot signal.
 * Requires secure boot to be present and true (1).
 */
RiskDecision integrity_rule(const RiskInput* input) {
    for (size_t i = 0; i < input->signal_count; i++) {
        if (input->signals[i].signal_id == SIGNAL_SECURE_BOOT) {
            return input->signals[i].normalized_value ? RISK_ALLOW : RISK_DENY;
        }
    }
    return RISK_DENY;
}
