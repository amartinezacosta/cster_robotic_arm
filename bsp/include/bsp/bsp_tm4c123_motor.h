#ifndef BSP_TM4C123_MOTOR_H
#define BSP_TM4C123_MOTOR_H

#include <stdint.h>

#define PWM_FREQUENCY       (80000UL - 1UL)

#define MOTOR_0_PWM_PINS    (BIT4 | BIT5)
#define MOTOR_1_PWM_PINS    (BIT6 | BIT7)
#define MOTOR_2_PWM_PINS    (BIT0 | BIT1)

#define MOTOR_0_ENCODER_PINS (BIT2 | BIT3)
#define MOTOR_1_ENCODER_PINS (BIT4 | BIT5)
#define MOTOR_2_ENCODER_PINS (BIT6 | BIT7)

#define MOTORS_ENCODER_PINS   (MOTOR_0_ENCODER_PINS |\
                               MOTOR_1_ENCODER_PINS |\
                               MOTOR_2_ENCODER_PINS)

typedef enum 
{
  CLOCKWISE,
  COUNTER_CLOCKWISE
}motor_dir_t;

void bsp_motors_init(void);

void bsp_motor_0_speed(uint32_t speed, motor_dir_t dir);
void bsp_motor_1_speed(uint32_t speed, motor_dir_t dir);
void bsp_motor_2_speed(uint32_t speed, motor_dir_t dir);

void bsp_motor_power_enable(void);
void bsp_motor_power_disable(void);

int32_t bsp_motor_0_encoder(void);
int32_t bsp_motor_1_encoder(void);
int32_t bsp_motor_2_encoder(void);


#endif