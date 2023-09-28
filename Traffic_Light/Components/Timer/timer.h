#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <stdbool.h>

typedef void (*timeout_cb)(void);

void timer_init(void);
bool timer_start(uint16_t time, timeout_cb p_timeout_cb);
void timer_stop(void);

#endif