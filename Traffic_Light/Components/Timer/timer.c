#include "timer.h"
#include "tim.h"

static timeout_cb timeout_ring;

void timer_init(void)
{
}	

bool timer_start(uint16_t time, timeout_cb p_timeout_cb)
{
	bool status = true;
	if ((time > 0) && (p_timeout_cb != NULL))
	{
		HAL_TIM_Base_Stop_IT(&htim6);
		__HAL_TIM_SET_AUTORELOAD(&htim6, time);
		__HAL_TIM_SET_COUNTER(&htim6, 0);
		__HAL_TIM_CLEAR_FLAG(&htim6, TIM_FLAG_UPDATE);
		HAL_TIM_Base_Start_IT(&htim6);
		timeout_ring = p_timeout_cb;
	}
	else
	{
		HAL_TIM_Base_Stop_IT(&htim6);
		status = false;
	}
	
	return status;
}

void timer_stop(void)
{
	HAL_TIM_Base_Stop_IT(&htim6);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim6)
	{
		HAL_TIM_Base_Stop_IT(&htim6);
		timeout_ring();
	}
}