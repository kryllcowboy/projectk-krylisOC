#ifndef LIGHT_H
#define LIGHT_H

typedef enum
{
	light_off,
	light_on,
}light_state_e_t;

typedef enum
{
	light_red,
	light_yelow,
	light_green,
	light_all,
}light_color_e_t;

void light_init(void);
void light_set_color_state(light_color_e_t color, light_state_e_t state);

#endif