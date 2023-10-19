#ifndef LED_DISPLAY_AUTO_H
#define LED_DISPLAY_AUTO_H

#include <stdint.h>

typedef enum
{
	LED_DISPLAY_AUTO_RED_TIME,
	LED_DISPLAY_AUTO_GREEN_TIME,
}led_display_auto_color_time_e_t;

void led_display_auto_init(void);
void led_display_auto_clear(void);
void led_display_auto_time(led_display_auto_color_time_e_t color, uint8_t time);

#endif