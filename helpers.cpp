#include <Arduino.h>
#include "helpers.h"

bool is_timeout_reached(uint32_t last_run, uint32_t timeout)
{
    return millis() - last_run >= timeout;
}
