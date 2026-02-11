#include "input/normalize.h"

/*
 * Clamps a raw signal value between the specified min and max bounds.
 * Returns -1 if inputs are invalid, 0 otherwise.
 */
int normalize_signal(const SignalMeta* meta, int64_t raw, int64_t* out) {
    if (!meta || !out) {
        return -1;
    }

    if (raw < meta->min) raw = meta->min;
    if (raw > meta->max) raw = meta->max;

    *out = raw;
    return 0;
}
