#ifndef FLAG_MACHINE_H
#define FLAG_MACHINE_H

typedef enum
{
	FLAG_BUTTON_PRESSED = 0,
}fm_flags_e_t;

void fm_init(void);
void fm_run(void);
void fm_set_flag(fm_flags_e_t flag);
void fm_clear_flag(fm_flags_e_t flag);

#endif