#ifndef BSP_TM4C123_UART_H
#define BSP_TM4C123_UART_H

#include <stdint.h>

#define UART0_RX_BUFFER_SIZE    64
#define UART0_TX_BUFFER_SIZE    64

void bsp_uart_init(void);
uint32_t bsp_uart_write(uint8_t *data, uint32_t size);
uint32_t bsp_uart_read(uint8_t *data, uint32_t size);

#endif
