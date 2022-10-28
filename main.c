#include <FreeRTOS.h>
#include <task.h>
#include <bsp_tm4c123.h>
#include <pid.h>

#include <string.h>
#include <stdlib.h>

pid_t motor_0_pid,
      motor_1_pid,
      motor_2_pid;

void motors_position_control_task(void *pvParamaters)
{
  const TickType_t xDelay = 20 / portTICK_PERIOD_MS;

  pid_init(&motor_0_pid,
           1.0f,
           0.0f,
           0.0f,
           80000.0f,
           8000.0f);

  pid_init(&motor_1_pid,
           1.0f,
           0.0f,
           0.0f,
           80000.0f,
           8000.0f);

  pid_init(&motor_2_pid,
           1.0f,
           0.0f,
           0.0f,
           80000.0f,
           8000.0f);

  /*Enable power to the motors, wait for voltage to settle*/
  bsp_motor_power_enable();
  vTaskDelay(3 / portTICK_PERIOD_MS);

  for( ;; )
  {
    /*Read motors encoder relative value*/
    uint32_t motor_0_encoder = bsp_motor_0_encoder();
    uint32_t motor_1_encoder = bsp_motor_1_encoder();
    uint32_t motor_2_encoder = bsp_motor_2_encoder();

    int32_t motor_0_output = (int32_t)pid_update(&motor_0_pid,
                                                 (float)motor_0_encoder,
                                                 0.02f);

    int32_t motor_1_output = (int32_t)pid_update(&motor_0_pid,
                                                 (float)motor_1_encoder,
                                                 0.02f);

    int32_t motor_2_output = (int32_t)pid_update(&motor_0_pid,
                                                 (float)motor_2_encoder,
                                                 0.02f);

    /*Find motor rotation direction*/
    motor_dir_t motor_0_dir = (motor_0_output < 0) ? CLOCKWISE : COUNTER_CLOCKWISE;
    motor_dir_t motor_1_dir = (motor_1_output < 0) ? CLOCKWISE : COUNTER_CLOCKWISE;
    motor_dir_t motor_2_dir = (motor_2_output < 0) ? CLOCKWISE : COUNTER_CLOCKWISE;

    /*Set PWM output to control motor speed*/
    bsp_motor_0_speed(abs(motor_0_output), motor_0_dir);
    bsp_motor_1_speed(abs(motor_0_output), motor_1_dir);
    bsp_motor_2_speed(abs(motor_0_output), motor_2_dir);

    vTaskDelay(xDelay);
  }
}

void serial_terminal_task(void *pvParameters)
{
  const char str[] = "cster robotic arm\r\n";
  const TickType_t xDelay = 500 / portTICK_PERIOD_MS;

  for( ;; )
  {
    bsp_uart_write((uint8_t*)str, strlen(str));
    vTaskDelay(xDelay);
  }
}

int main(void)
{
  /*Initialize the board peripherals*/
  bsp_init();

  /*Initialize FreeRTOS tasks*/
  xTaskCreate(motors_position_control_task,
    "motors_position_control_task",
    configMINIMAL_STACK_SIZE,
    NULL,
    1,
    NULL);

  xTaskCreate(serial_terminal_task,
    "serial_terminal_task",
    configMINIMAL_STACK_SIZE,
    NULL,
    0,
    NULL);

  /*Start FreeRTOS scheduler*/
  vTaskStartScheduler();

  /*Should  never hit this point*/
  for( ;; );
}
