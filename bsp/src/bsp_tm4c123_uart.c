#include <bsp_tm4c123_uart.h>
#include <TM4C123.h>

void bsp_uart_init(void)
{
  /*Enable UART0 clock*/
  SYSCTL->RCGCUART |= SYSCTL_RCGCUART_R0;
  while(!(SYSCTL->PRUART & SYSCTL_PRUART_R0));

  /*Enable GPIOA clock*/
  SYSCTL->RCGCGPIO |= SYSCTL_RCGCGPIO_R0;
  while(!(SYSCTL->PRGPIO & SYSCTL_PRGPIO_R0));

  /*GPIO alternate function select and digital enable*/
  GPIOA->AFSEL |= (BIT0 | BIT1);
  GPIOA->DEN |= (BIT0 | BIT1);

  /*GPIO pin mux control select*/
  GPIOA->PCTL |= GPIO_PCTL_PA0_U0RX |
                GPIO_PCTL_PA1_U0TX;

  /*Disable UART0*/
  UART0->CTL &= ~UART_CTL_UARTEN;

  /*Set Baudrate divisor configuration,
   see https://www.ti.com/lit/ds/symlink/tm4c1233h6pm.pdf page 875*/

   /*Baudrate based on a clock of 80MHz*/
  /*BRD = 80,000,000 / (16 * 115200) = 43.4027 = 43*/
  /*FBRD = int(0.4027 * 64 + 0.5) = 6.9432 = 6*/
  UART0->IBRD = 43UL;
  UART0->FBRD = 6UL;

  /*8-bit data, no parity, one stop bit*/
  UART0->LCRH = UART_LCRH_WLEN_8;

  /*Select PLL clock source*/
  UART0->CC = SSI_CC_CS_SYSPLL;

  /*Enable UART*/
  UART0->CTL |= UART_CTL_UARTEN;
}

void bsp_uart_write(uint8_t *data, uint32_t size)
{
  for(uint32_t i = 0; i < size; i++)
  {
    while(UART0->FR & UART_FR_TXFF);
    UART0->DR = data[i];
  }
}

void bsp_uart_read(uint8_t *data, uint32_t size)
{
  for(uint32_t i = 0; i < size; i++)
  {
    while(UART0->FR & UART_FR_RXFE);
    data[i] = UART0->DR;
  }
}
