#include "led_display.h"
#include <string.h>
#include <stdio.h>

#define LED_DISPLEY_BIT_DELAY 20

#define led_display_COMM1    0x40
#define led_display_COMM2    0xC0
#define led_display_COMM3    0x80

const uint8_t led_display_digit[] =
  {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
const uint8_t led_display_on[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
const uint8_t led_display_off[6] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
const uint8_t led_display_minus = 0x40;
const uint8_t led_display_dot = 0x80;  

/* Timeout for creation pulse */
void led_display_delay_us(uint8_t delay)
{
  while (delay > 0)
  {
    delay--;
    __nop();__nop();__nop();__nop();
  }
}

/* Interface LED Driver tm1637 */
/* Start communication with LED driver tm1637 */
static void led_display_start(led_display_s_t *led_display)
{
  HAL_GPIO_WritePin(led_display->gpio_dat, led_display->pin_dio, GPIO_PIN_RESET);
  led_display_delay_us(LED_DISPLEY_BIT_DELAY);
}

/* Stop communication with LED driver tm1637 */
static void led_display_stop(led_display_s_t *led_display)
{
  HAL_GPIO_WritePin(led_display->gpio_dat, led_display->pin_dio, GPIO_PIN_RESET);
  led_display_delay_us(LED_DISPLEY_BIT_DELAY);
  HAL_GPIO_WritePin(led_display->gpio_clk, led_display->pin_clk, GPIO_PIN_SET);
  led_display_delay_us(LED_DISPLEY_BIT_DELAY);
  HAL_GPIO_WritePin(led_display->gpio_dat, led_display->pin_dio, GPIO_PIN_SET);
  led_display_delay_us(LED_DISPLEY_BIT_DELAY);
}

/* Communication with LED driver tm1637 */
static uint8_t led_display_write_byte(led_display_s_t *led_display, uint8_t data)
{
	//  write 8 bit data
	for (uint8_t i = 0; i < 8; i++)
	{
		HAL_GPIO_WritePin(led_display->gpio_clk, led_display->pin_clk, GPIO_PIN_RESET);
		led_display_delay_us(LED_DISPLEY_BIT_DELAY);
		if (data & 0x01)
		{
			HAL_GPIO_WritePin(led_display->gpio_dat, led_display->pin_dio, GPIO_PIN_SET);
		}
		else
		{
			HAL_GPIO_WritePin(led_display->gpio_dat, led_display->pin_dio, GPIO_PIN_RESET);
		}
		led_display_delay_us(LED_DISPLEY_BIT_DELAY);
		HAL_GPIO_WritePin(led_display->gpio_clk, led_display->pin_clk, GPIO_PIN_SET);
		led_display_delay_us(LED_DISPLEY_BIT_DELAY);
		data = data >> 1;
	}
	
	// wait for acknowledge
	HAL_GPIO_WritePin(led_display->gpio_clk, led_display->pin_clk, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(led_display->gpio_dat, led_display->pin_dio, GPIO_PIN_SET);
	led_display_delay_us(LED_DISPLEY_BIT_DELAY);
	HAL_GPIO_WritePin(led_display->gpio_clk, led_display->pin_clk, GPIO_PIN_SET);
	led_display_delay_us(LED_DISPLEY_BIT_DELAY);
	uint8_t ack = HAL_GPIO_ReadPin(led_display->gpio_dat, led_display->pin_dio);
	if (ack == 0)
	{
		HAL_GPIO_WritePin(led_display->gpio_dat, led_display->pin_dio, GPIO_PIN_RESET);
	}
	led_display_delay_us(LED_DISPLEY_BIT_DELAY);
	HAL_GPIO_WritePin(led_display->gpio_clk, led_display->pin_clk, GPIO_PIN_RESET);
	led_display_delay_us(LED_DISPLEY_BIT_DELAY);
	return ack;
}

/*********************************************************************************************************************/
/* Initialization LED Display */
void led_display_init(led_display_s_t *led_display, GPIO_TypeDef *gpio_clk, uint16_t pin_clk, GPIO_TypeDef *gpio_dat, uint16_t pin_dat)
{
	// Clear configuration for LED Display
	memset(led_display, 0, sizeof(led_display_s_t));

	// Fill configuration for LED Display
	led_display->gpio_clk = gpio_clk;
	led_display->pin_clk = pin_clk;
	led_display->gpio_dat = gpio_dat;
	led_display->pin_dio = pin_dat;
	
	// Initialization GPIO for current LED Display
	GPIO_InitTypeDef led_pins = {0};
	led_pins.Mode  = GPIO_MODE_OUTPUT_OD;
	led_pins.Pull  = GPIO_NOPULL;
	led_pins.Speed = GPIO_SPEED_FREQ_HIGH;
	
	// Init clk pin
	led_pins.Pin   = pin_clk;
	HAL_GPIO_Init(gpio_clk, &led_pins);
	
	// Init clk pin
	led_pins.Pin = pin_dat;
	HAL_GPIO_Init(gpio_dat, &led_pins); 
	
	// Set max brightess
	led_display_brightness(led_display, 7); 
}

/* Set display brightness */
void led_display_brightness(led_display_s_t *led_display, uint8_t brightness_0_to_7)
{
	led_display->brightness = (brightness_0_to_7 & 0x7) | 0x08;
}

/* Write data to LED Display */
void led_display_write_data(led_display_s_t *led_display, const uint8_t *data, uint8_t length, uint8_t pos)
{
	// Check input parameters
	if (pos > 5)
	{
		return;
	}
	if (length > 6)
	{
		length = 6;
	}
	
	// write COMM1
	led_display_start(led_display);
	led_display_write_byte(led_display, led_display_COMM1);
	led_display_stop(led_display);
	
	// write COMM2 + first digit address
	led_display_start(led_display);
	led_display_write_byte(led_display, led_display_COMM2 + (pos & 0x03));
	
	// write the data bytes
	for (uint8_t i = 0; i < length; i++)
	{
		led_display_write_byte(led_display, data[i]);
	}
	led_display_stop(led_display);
	
	// write COMM3 + brightness
	led_display_start(led_display);
	led_display_write_byte(led_display, led_display_COMM3 + led_display->brightness);
	led_display_stop(led_display);
}

/* Write segments */
void led_display_write_segment(led_display_s_t *led_display, const uint8_t *segments, uint8_t length, uint8_t pos)
{
	led_display_write_data(led_display, segments, length, pos);
}

/* Write Digital Value to LED Display */
void led_display_write_int(led_display_s_t *led_display, int16_t digit, uint8_t pos)
{
	char str[7];
	uint8_t buffer[6] = {0};
	snprintf(str, sizeof(str) , "%d", digit);
	for (uint8_t i=0; i < 6; i++)
	{
		if (str[i] == '-')
		{
			buffer[i] = led_display_minus;
		}
		else if((str[i] >= '0') && (str[i] <= '9'))
		{
			buffer[i] = led_display_digit[str[i] - 48];
		}
		else
		{
			buffer[i] = 0;
			break;
		}
		led_display_write_data(led_display, buffer, 6, pos);
	}	
}

/* Enabled or Disabled all segments LED Display */
void led_display_fill(led_display_s_t *led_display, bool enable)
{
	if (enable)
	{
		led_display_write_segment(led_display, led_display_on, 6, 0);
	}
	else
	{
		led_display_write_segment(led_display, led_display_off, 6, 0);	
	}		
}
