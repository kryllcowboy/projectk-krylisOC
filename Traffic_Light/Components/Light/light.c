#include "light.h"
#include "gpio.h"

void light_init(void)
{
	light_set_color_state(light_all, light_off);
}	

void light_set_color_state(light_color_e_t color, light_state_e_t state)
{
	switch (color)
	{
		case light_red:
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, (GPIO_PinState)state);
			break;
		}
		case light_yelow:
		{
			HAL_GPIO_WritePin(LED_YELOW_GPIO_Port, LED_YELOW_Pin, (GPIO_PinState)state);
			break;
		}
		case light_green:
		{
			HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, (GPIO_PinState)state);
			break;
		}
		case light_all:
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, (GPIO_PinState)state);
			HAL_GPIO_WritePin(LED_YELOW_GPIO_Port, LED_YELOW_Pin, (GPIO_PinState)state);
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, (GPIO_PinState)state);
			break;
		}
		default:
		{
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_YELOW_GPIO_Port, LED_YELOW_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET);
			break;
		}
  }
}