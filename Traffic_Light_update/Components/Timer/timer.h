#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <stdbool.h>

typedef void (*timer_cb)(void);

typedef enum
{
	TIMER_NONE  = 0,
	TIMER_PWM_5 = 5,
}timer_id_e_t;

typedef struct
{
	/* Controls */
	timer_id_e_t id;
	uint32_t htim;
	/* Parameters */
	uint16_t period;
	uint16_t channel_1;
	uint16_t channel_2;
	uint16_t channel_3;
	uint16_t channel_4;
	/* Callbacks*/
	timer_cb update_cb;
	timer_cb channel_1_cb;
	timer_cb channel_2_cb;
	timer_cb channel_3_cb;
	timer_cb channel_4_cb;
}timer_pwm_s_t;

void timer_init(void);
void timer_pwm_init(timer_pwm_s_t * timer_pwm);
void timer_pwm_start(timer_pwm_s_t * timer_pwm);
void timer_pwm_update(timer_pwm_s_t * timer_pwm);
bool timer_deinit_pwm(timer_pwm_s_t * timer_pwm);
bool timer_start(uint16_t time, timer_cb p_timeout_cb);
void timer_stop(void);

#endif