#ifndef BSP_TM4C123_LED_H
#define BSP_TM4C123_LED_H

typedef enum
{
  ON,
  OFF
}led_value_t;

void bsp_led_init(void);
void bsp_red_led(led_value_t value);
void bsp_green_led(led_value_t value);
void bsp_blue_led(led_value_t value);

void bsp_red_led_toggle(void);
void bsp_green_led_toggle(void);
void bsp_blue_led_toggle(void);

#endif
