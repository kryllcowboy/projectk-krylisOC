#include "app.h"
#include "light.h"
#include "timer.h"
#include "button.h"
#include "stm32f4xx_hal.h"
#include "flag_machine.h"
#include "led_display_auto.h"

// Variants
/*
1. Red
2. Red + Yelow
3. Green
4. Green blink
5. Yelow
*/

typedef enum
{
	red = 0,
	red_yelow,
	green,
	green_blink,
	yelow,
}trafic_light_mode_e_t;

//Red - 30 s; Red + Yelow - 3 s; Green - 15 s; Green blink - 4 s; Yelow - 3 s; blink - 0.5/0.5 s

static trafic_light_mode_e_t trafic_light_mode = green;
static uint8_t trafic_light_blink = 0;

static void app_change_mode(void);

void app_init(void)
{
	timer_init();
	light_init();
	led_display_auto_init();
//	button_init(app_change_mode);	
//	timer_start(500, app_change_mode);
//	light_set_color_state(auto_trafic_light, light_all, light_on);
//	light_set_color_state(pedestrian_trafic_light, light_all, light_on);
}	

void app_run(void)
{
//	trafic_light_mode = green;
	while(1)
	{
		
	}
}

static void app_change_mode(void)
{
	switch (trafic_light_mode)
	{		
		case red:
		{
			light_set_color_state(auto_trafic_light, light_all, light_off);
			light_set_color_state(auto_trafic_light, light_red, light_on);
			timer_start(30000, app_change_mode);
			trafic_light_mode = red_yelow;
			break;
		}
		case red_yelow:
		{
			light_set_color_state(auto_trafic_light, light_yelow, light_on);
			timer_start(3000, app_change_mode);
			trafic_light_mode = green;
			break;
		}
		case green:
		{			
			light_set_color_state(auto_trafic_light, light_all, light_off);
			light_set_color_state(auto_trafic_light, light_green, light_on);
			trafic_light_mode = green_blink;
			trafic_light_blink = 8;
			break;
		}
		case green_blink:
		{
			if ((trafic_light_blink % 2) == 0)
			{
				light_set_color_state(auto_trafic_light, light_green, light_off);
				timer_start(500, app_change_mode);
			}
			else
			{
				light_set_color_state(auto_trafic_light, light_green, light_on);
				timer_start(500, app_change_mode);
			}
			trafic_light_blink --;
			if (trafic_light_blink == 0)
			{
				trafic_light_mode = yelow;
			}
			break;
		}
		case yelow:
		{
			light_set_color_state(auto_trafic_light, light_green, light_off);
			light_set_color_state(auto_trafic_light, light_yelow, light_on);
			timer_start(3000, app_change_mode);
			trafic_light_mode = red;
			break;
		}
	}
}
