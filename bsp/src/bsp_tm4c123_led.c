#include <bsp_tm4c123_led.h>
#include <TM4C123.h>

void bsp_led_init(void)
{
  SYSCTL->RCGCGPIO |= SYSCTL_RCGCGPIO_R5;
  while(!(SYSCTL->PRGPIO & SYSCTL_PRGPIO_R5));

  GPIOF->DIR |= (BIT0 | BIT1 | BIT2);
  GPIOF->DEN |= (BIT0 | BIT1 | BIT2);
}

void bsp_red_led(led_value_t value)
{
  if(value == ON)
  {
    GPIOF->DATA |= BIT0;
  }
  else
  {
    GPIOF->DATA &= ~BIT0;
  }
}

void bsp_red_led_toggle(void)
{
  GPIOF->DATA ^= BIT0;
}

void bsp_green_led(led_value_t value)
{
  if(value == ON)
  {
    GPIOF->DATA |= BIT1;
  }
  else
  {
    GPIOF->DATA &=~ BIT1;
  }
}

void bsp_green_led_toggle(void)
{
  GPIOF->DATA ^= BIT1;
}

void bsp_blue_led(led_value_t value)
{
  if(value == ON)
  {
    GPIOF->DATA |= BIT2;
  }
  else
  {
    GPIOF->DATA &=~ BIT2;
  }
}

void bsp_blue_led_toggle(void)
{
  GPIOF->DATA ^= BIT2;
}




