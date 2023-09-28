#include "app.h"
#include "light.h"
#include "timer.h"
#include "stm32f4xx_hal.h"



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
	green,
	yelow,
  red,
  green_blink,
  yelow_blink,
  red_blink,
}
trafic_light_mode_e_t;

//Red - 30 s; Red + Yelow - 3 s; Green - 15 s; Green blink - 4 s; Yelow - 3 s; blink - 0.5/0.5 s

static trafic_light_mode_e_t trafic_light_mode = green_blink;
static uint8_t trafic_light_blink = 0;

static void app_change_mode(void);

void app_init(void)
{
	timer_init();
	light_init();
	
	timer_start(500, app_change_mode);
}	

void app_run(void)
{
	trafic_light_mode = green;
	while(1)
	{

	}
}

static void app_change_mode(void)
{
    switch (trafic_light_mode)
    {
//        case green:
//        {
//            light_set_color_state(light_green, light_on);
//            timer_start(500, app_change_mode);
//            trafic_light_mode = green_blink; 
//            break;
//        }
//        case green_blink:
//        {
//            light_set_color_state(light_green, light_off);
//            light_set_color_state(light_yelow, light_on);
//            timer_start(500, app_change_mode);
//            trafic_light_mode = yelow; 
//            break;
//        }
//        case yelow:
//        {
//            light_set_color_state(light_yelow, light_off);
//            light_set_color_state(light_red, light_on);
//            timer_start(5000, app_change_mode);
//            trafic_light_mode = red; 
//            break;
//        }
//        case red:
//        {
//            light_set_color_state(light_all, light_off);
//            light_set_color_state(light_green, light_on);
//            timer_start(500, app_change_mode);
//            trafic_light_mode = green; 
//            break;
//        }
//    }
//}


		light_set_color_state(light_green, light_on);
		HAL_Delay(1000);
		light_set_color_state(light_green, light_off);
    
		light_set_color_state(light_yelow, light_on);
		HAL_Delay(1000);
    light_set_color_state(light_yelow, light_off);	
		
		light_set_color_state(light_red, light_on);
		HAL_Delay(1000);
    light_set_color_state(light_red, light_off);
  }
}