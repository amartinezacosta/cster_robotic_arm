#ifndef BSP_TM4C123_UDMA_H
#define BSP_TM4C123_UDMA_H

#include <stdint.h>

#define UDMA_UART0_RX_CH   8
#define UDMA_UART0_TX_CH   9

typedef struct
{
  uint32_t source;
  uint32_t destination;
  uint32_t control;
  uint32_t unused;
}udma_table_entry_t;

void bsp_udma_init(void);

#endif
