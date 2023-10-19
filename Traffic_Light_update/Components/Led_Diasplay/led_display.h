#ifndef LED_DISPLAY_H
#define LED_DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"

typedef struct
{
	GPIO_TypeDef *gpio_clk;
	GPIO_TypeDef *gpio_dat;
	uint16_t     pin_clk;   
	uint16_t     pin_dio;  
	uint8_t      brightness;
}led_display_s_t;

void led_display_init(led_display_s_t *led_display, GPIO_TypeDef *gpio_clk, uint16_t pin_clk, GPIO_TypeDef *gpio_dat, uint16_t pin_dat);
void led_display_brightness(led_display_s_t *led_display, uint8_t brightness_0_to_7);
void led_display_write_segment(led_display_s_t *led_display, const uint8_t *segments, uint8_t length, uint8_t pos);
void led_display_write_int(led_display_s_t *led_display, int16_t data, uint8_t pos);
void led_display_fill(led_display_s_t *led_display, bool enable);

#endif
