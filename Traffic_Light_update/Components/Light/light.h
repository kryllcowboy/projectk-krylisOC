#ifndef LIGHT_H
#define LIGHT_H

typedef enum
{
	light_on  = 0,
	light_off = 1,
}light_state_e_t;

typedef enum
{
	light_red,
	light_yelow,
	light_green,
	light_all,
}light_color_e_t;

typedef enum
{
	auto_trafic_light,
	pedestrian_trafic_light
}trafic_light_e_t;

void light_init(void);
void light_set_color_state(trafic_light_e_t type_trafic_light, light_color_e_t color, light_state_e_t state);

#endif