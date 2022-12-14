#include <bsp_tm4c123.h>

int main(void)
{
  bsp_init();

  uint8_t c;
  for( ;; )
  {
    /*Read one byte*/
    if(bsp_uart_read(&c, 1))
    {
      /*Echo this byte*/
      bsp_uart_write(&c, 1);
    }
  }

}
