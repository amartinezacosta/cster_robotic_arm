#include <FreeRTOS.h>
#include <task.h>

#include <bsp_tm4c123.h>
#include <shell.h>
#include <string.h>
#include <TM4C123.h>

#define SHELL_BUFFER_SIZE   64

void shell_task(void *pvParameters);

/*Shell command callbacks*/
uint32_t motor_cmd_callback(uint32_t argc, pToken_t argv);

int main(void)
{
  bsp_init();

  xTaskCreate(shell_task,
              "shell task",
              configMINIMAL_STACK_SIZE,
              NULL,
              0,
              NULL);

  vTaskStartScheduler();

  for( ;; );
}

void shell_task(void *pvParameters)
{
  shell_t shell;

  shell_ctor(&shell,
             bsp_uart_write,
             bsp_uart_read);

  shell_register(&shell,
                 "motor",
                 motor_cmd_callback,
                 "Command to interface with motors");

  char str[SHELL_BUFFER_SIZE];
  for( ;; )
  {
    shell_prompt(&shell);
    shell_gets(&shell, str, SHELL_BUFFER_SIZE);
    uint32_t result = shell_run(&shell, str);
    shell_print_result(&shell, result);
  }
}

uint32_t motor_cmd_callback(uint32_t argc, pToken_t argv)
{
  uint32_t result;

  for(uint32_t i = 1; i < argc; i++)
  {
    if(strcmp("-i", argv[i]) == 0)
    {
      result = SHELL_OK;
    }
    else if(strcmp("-p", argv[i]) == 0)
    {
      result = SHELL_OK;
    }
    else
    {
      result = SHELL_CMD_NOT_FOUND;
      break;
    }
  }

  return result;
}
