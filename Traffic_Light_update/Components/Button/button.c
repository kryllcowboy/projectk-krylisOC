#include "button.h"
#include <stdint.h>
#include "gpio.h"
#include "stdbool.h"
#include "flag_machine.h"

void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
	if(pin == BUTTON_Pin)
	{
		fm_set_flag(FLAG_BUTTON_PRESSED);
	}
}
