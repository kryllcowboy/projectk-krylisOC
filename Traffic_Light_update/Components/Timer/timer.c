#include "timer.h"
#include "tim.h"
#include <string.h>

static timer_cb timeout_ring;

#define TIMERES_PWM_CONFIG_NUMBER 5

static timer_pwm_s_t timer_pwm_context[TIMERES_PWM_CONFIG_NUMBER];

void timer_init(void)
{
	memset(&timer_pwm_context, 0, TIMERES_PWM_CONFIG_NUMBER * sizeof(timer_pwm_s_t));
}

void timer_pwm_init(timer_pwm_s_t * timer_pwm)
{
	for (uint8_t i = 0; i < TIMERES_PWM_CONFIG_NUMBER; i ++)
	{
		if (timer_pwm->id == TIMER_PWM_5)
		{
			timer_pwm->htim = (uint32_t)&htim5;
			memcpy(&timer_pwm_context[i], timer_pwm, sizeof(timer_pwm_s_t));
			timer_pwm_update(timer_pwm);
			break;
		}
	}
}

void timer_pwm_update(timer_pwm_s_t * timer_pwm)
{
	__HAL_TIM_SET_AUTORELOAD((TIM_HandleTypeDef *)timer_pwm->htim, timer_pwm->period);
	__HAL_TIM_SET_COMPARE((TIM_HandleTypeDef *)timer_pwm->htim, TIM_CHANNEL_1, timer_pwm->channel_1);
	__HAL_TIM_SET_COMPARE((TIM_HandleTypeDef *)timer_pwm->htim, TIM_CHANNEL_2, timer_pwm->channel_2);
	__HAL_TIM_SET_COMPARE((TIM_HandleTypeDef *)timer_pwm->htim, TIM_CHANNEL_3, timer_pwm->channel_3);
	__HAL_TIM_SET_COMPARE((TIM_HandleTypeDef *)timer_pwm->htim, TIM_CHANNEL_4, timer_pwm->channel_4);
}

void timer_pwm_start(timer_pwm_s_t * timer_pwm)
{
	HAL_TIM_Base_Start_IT((TIM_HandleTypeDef *)timer_pwm->htim);
	if (timer_pwm->channel_1_cb != NULL)
	{
		HAL_TIM_PWM_Start_IT((TIM_HandleTypeDef *)timer_pwm->htim, TIM_CHANNEL_1);
	}
	if (timer_pwm->channel_2_cb != NULL)
	{
		HAL_TIM_PWM_Start_IT((TIM_HandleTypeDef *)timer_pwm->htim, TIM_CHANNEL_2);
	}
	if (timer_pwm->channel_3_cb != NULL)
	{
		HAL_TIM_PWM_Start_IT((TIM_HandleTypeDef *)timer_pwm->htim, TIM_CHANNEL_3);
	}
	if (timer_pwm->channel_4_cb != NULL)
	{
		HAL_TIM_PWM_Start_IT((TIM_HandleTypeDef *)timer_pwm->htim, TIM_CHANNEL_4);
	}
}

void timer_pwm_stop(const timer_pwm_s_t * timer_pwm)
{
	if (timer_pwm->channel_1_cb != NULL)
	{
		HAL_TIM_PWM_Stop_IT((TIM_HandleTypeDef *)timer_pwm->htim, TIM_CHANNEL_1);
	}
	if (timer_pwm->channel_2_cb != NULL)
	{
		HAL_TIM_PWM_Stop_IT((TIM_HandleTypeDef *)timer_pwm->htim, TIM_CHANNEL_2);
	}
	if (timer_pwm->channel_3_cb != NULL)
	{
		HAL_TIM_PWM_Stop_IT((TIM_HandleTypeDef *)timer_pwm->htim, TIM_CHANNEL_3);
	}
	if (timer_pwm->channel_4_cb != NULL)
	{
		HAL_TIM_PWM_Stop_IT((TIM_HandleTypeDef *)timer_pwm->htim, TIM_CHANNEL_4);
	}
}

bool timer_start(uint16_t time, timer_cb p_timeout_cb)
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
	for (uint8_t i = 0; i < TIMERES_PWM_CONFIG_NUMBER; i ++)
	{
		if (htim == (TIM_HandleTypeDef *)timer_pwm_context[i].htim)
		{
			if (timer_pwm_context[i].update_cb != NULL)
			{
				timer_pwm_context[i].update_cb();
			}
		}
	}
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	for (uint8_t i = 0; i < TIMERES_PWM_CONFIG_NUMBER; i ++)
	{
		if (htim == (TIM_HandleTypeDef *)timer_pwm_context[i].htim)
		{
			if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
			{
				if (timer_pwm_context[i].channel_1_cb != NULL)
				{
					timer_pwm_context[i].channel_1_cb();
				}
			}
			if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
			{
				if (timer_pwm_context[i].channel_2_cb != NULL)
				{
					timer_pwm_context[i].channel_2_cb();
				}
			}
			if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
			{
				if (timer_pwm_context[i].channel_3_cb != NULL)
				{
					timer_pwm_context[i].channel_3_cb();
				}
			}
			if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
			{
				if (timer_pwm_context[i].channel_4_cb != NULL)
				{
					timer_pwm_context[i].channel_4_cb();
				}
			}
		}
	}
}