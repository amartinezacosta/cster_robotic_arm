#include <bsp_tm4c123.h>

int main(void)
{
  /*Initialize board peripherals*/
  bsp_init();

  /*Initialize RTOS*/
  bsp_motor_power_enable();

  bsp_motor_0_speed(200, CLOCKWISE);
  int32_t encoder_0 = bsp_motor_0_encoder();

  /*Let RTOS do its thing*/
  while(1)
  {

  }
}
