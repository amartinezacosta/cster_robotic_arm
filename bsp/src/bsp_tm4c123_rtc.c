#include <bsp_tm4c123_rtc.h>
#include <TM4C123.h>

uint32_t bsp_rtc_seconds(void)
{
  uint32_t time = HIB->RTCC;
  return time;
}
