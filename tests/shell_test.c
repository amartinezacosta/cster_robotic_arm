#include <bsp_tm4c123.h>
#include <shell.h>

int main(void)
{
  bsp_init();

  shell_t shell;
  char *test_cmd = "motor -i 0 -p 1023";

  shell_run(&shell, test_cmd);

  for( ;; )
  {

  }
}
