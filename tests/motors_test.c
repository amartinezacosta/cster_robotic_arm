#include <bsp_tm4c123.h>
#include <TM4C123.h>

#define RUN_ITERATIONS 10000

int main(void)
{
  bsp_init();

  /*Enable power to motors*/
  bsp_motor_power_enable();
  for(int i = 0; i < 10000; i++);

  /*Disable sleep mode*/
  bsp_motor_sleep_disable();

  /*Run motors and record last positions*/
  bsp_motor_0_speed(40000, CLOCKWISE);
  bsp_motor_1_speed(40000, CLOCKWISE);
  bsp_motor_2_speed(40000, CLOCKWISE);

  for(int i = 0; i < 10000; i++);

  int32_t motor_0_encoder = bsp_motor_0_encoder();
  int32_t motor_1_encoder = bsp_motor_1_encoder();
  int32_t motor_2_encoder = bsp_motor_2_encoder();

  /*Go to sleep*/
  SCB->SCR |= (SCB_SCR_SLEEPONEXIT_Pos << 1);
  //__WFI();
}