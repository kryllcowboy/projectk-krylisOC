#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include <stdbool.h>

typedef void (*button_pressed_cb)(void);

void button_init(button_pressed_cb p_button_pressed_cb);

void button_disable(void);

void button_enable(void);

#endif