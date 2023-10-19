#include "led_display_auto.h"
#include "led_display.h"
#include "gpio.h"

led_display_s_t led_display_auto;

void led_display_auto_init(void)
{
	led_display_init(&led_display_auto, AUTO_TIME_CLK_GPIO_Port, AUTO_TIME_CLK_Pin, AUTO_TIME_DATA_GPIO_Port, AUTO_TIME_DATA_Pin);
	led_display_fill(&led_display_auto, false);
}	

void led_display_auto_clear(void)
{
	led_display_fill(&led_display_auto, false);
}

void led_display_auto_time(led_display_auto_color_time_e_t color, uint8_t time)
{
	if (LED_DISPLAY_AUTO_RED_TIME == color)
	{
		led_display_write_int(&led_display_auto, time, 2);
	}
	else
	{
		led_display_write_int(&led_display_auto, time, 4);
	}
}