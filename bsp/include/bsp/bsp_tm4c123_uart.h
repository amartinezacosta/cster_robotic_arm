#ifndef BSP_TM4C123_UART_H
#define BSP_TM4C123_UART_H

#include <stdint.h>

void bsp_uart_init(void);
void bsp_uart_write(uint8_t *data, uint32_t size);
void bsp_uart_read(uint8_t *data, uint32_t size);

#endif
