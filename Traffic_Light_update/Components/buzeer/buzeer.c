#include "buzzer.h"
#include "main.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_hal.h"


uint16_t frequency = 1000;
uint16_t frequency_step = 100; 


void buzzer_init(void)
{

}

 void buzzer_run()
{
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
  
 while (1) 
{
    for (int i = 0; i < 10; i++) 
   {
      frequency += frequency_step;
      HAL_Delay(1000 / frequency);
     
      if (frequency > 4000) 
      {
       HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
      }
   }
}
}  