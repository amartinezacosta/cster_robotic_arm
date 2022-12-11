#include <bsp_tm4c123_udma.h>
#include <TM4C123.h>

udma_table_entry_t udma_control_table[64] __attribute__((aligned(1024)));

void bsp_udma_init(void)
{
  /*Enable the μDMA clock using the RCGCDMA register*/
  SYSCTL->RCGCDMA |= SYSCTL_RCGCDMA_R0;
  while(!(SYSCTL->PRDMA & SYSCTL_PRDMA_R0));

  /*Enable the μDMA controller by setting the MASTEREN bit*/
  UDMA->CFG |= UDMA_CFG_MASTEN;

  /*Program the location of the channel control table by 
    writing the base address of the table*/
  UDMA->CTLBASE = (uint32_t)&udma_control_table[0];
}



