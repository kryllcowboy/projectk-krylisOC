#include "app.h"
#include "gpio.h"


void app_init(void)
{
}

void app_run(void)
{
  while(1)
  {
    GPIOD -> ODR = 0x3000;
  HAL_Delay(500);
  GPIOD -> ODR = 0x0000; 
  HAL_Delay(500);
    
  GPIOC -> ODR = 0xC000;
  HAL_Delay(500);
  GPIOC -> ODR &= ~0xC000; 
  HAL_Delay(500);
  }
  
}

