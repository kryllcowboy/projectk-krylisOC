#include "button.h"
#include "gpio.h"
#include <stdint.h>



static button_pressed_cb button_pressed;

void button_init(button_pressed_cb p_button_pressed_cb)
{
 button_pressed = p_button_pressed_cb;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == BUTTON_Pin)
  {
    button_pressed();
    button_disable();
  }
}

void button_disable(void)
{
  HAL_NVIC_DisableIRQ(EXTI0_IRQn);
}

void button_enable(void)
{
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}
  