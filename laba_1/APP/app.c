#include "app.h"
#include "gpio.h"


void app_init(void)
{
}

void app_run(void)
{
  while(1)
  {
  GPIOD -> ODR = 0xF000;
  HAL_Delay(400);
  GPIOD -> ODR = 0x0000; 
  HAL_Delay(200);
 
   
  }
  
}

