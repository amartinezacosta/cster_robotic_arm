#include <bsp_tm4c123.h>
//#include <TM4C123.h>

int main(void)
{
  bsp_init();

  char str[15] = "Hello World DMA";
  //uint8_t buffer[12];

  //bsp_uart_read(buffer, 5);

  for( ;; )
  {
    bsp_uart_write((uint8_t*)str, 15);
    /*Wait three seconds*/
    uint32_t t0 = bsp_rtc_seconds();
    while((bsp_rtc_seconds() - t0) < 3);
  }

}
