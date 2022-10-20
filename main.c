#include <FreeRTOS.h>
#include <task.h>
#include <bsp_tm4c123.h>

void simple_task(void *pvParamaters)
{
  for( ;; )
  {
    bsp_green_led(ON);
    for(uint32_t i = 0; i < 1000000; i++);
    bsp_green_led(OFF);
    for(uint32_t i = 0; i < 1000000; i++);
  }
}

int main(void)
{
  /*Initialize the board peripherals*/
  bsp_init();

  /*Initialize FreeRTOS tasks*/
  xTaskCreate(simple_task, 
    "simple_task",
    configMINIMAL_STACK_SIZE,
    NULL,
    0,
    NULL);

  /*Start FreeRTOS scheduler*/
  vTaskStartScheduler();

  /*Shoud never hit this point*/
  for( ;; );
}
