#include "buzzer.h"
#include "main.h"
#include "stm32f4xx_it.h"

void buzzer_init(void)
{

}

 void buzzer_run()
{
//buzzer_run(TBUZ_100, TICK_2);
  HAL_Delay(2000);
  
  while (1)
  {
//	  buzzer_run(TBUZ_50, TICK_4);
	  HAL_Delay(2000);
  }
}
  