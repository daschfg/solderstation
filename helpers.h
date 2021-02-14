#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <stdint.h>

#define ARRAYSIZE(a)    (sizeof(a)/sizeof(a[0]))

bool is_timeout_reached(uint32_t last_run, uint32_t timeout);

#endif
