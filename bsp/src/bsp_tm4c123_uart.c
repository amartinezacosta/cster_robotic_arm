#include <bsp_tm4c123_uart.h>
#include <bsp_tm4c123_ringbuffer.h>
#include <TM4C123.h>

uint8_t uart0_tx_buffer[UART0_TX_BUFFER_SIZE];
uint8_t uart0_rx_buffer[UART0_RX_BUFFER_SIZE];

ringbuffer_t uart0_tx_ringbuffer;
ringbuffer_t uart0_rx_ringbuffer;

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

  /*Enable UART with interrupts*/
  UART0->CTL |= ( UART_CTL_UARTEN |
                  UART_CTL_TXE    |
                  UART_CTL_RXE );

  /*Clear UART interrupts*/
  UART0->ICR |= ( UART_ICR_RXIC |
                  UART_ICR_TXIC);

  /*Set UART interrupts*/
  UART0->IM |= UART_IM_RXIM;

  /*Construct ringbuffers*/
  ringbuffer_ctor(&uart0_tx_ringbuffer,
                  uart0_tx_buffer,
                  UART0_TX_BUFFER_SIZE);
  ringbuffer_ctor(&uart0_rx_ringbuffer,
                  uart0_rx_buffer,
                  UART0_RX_BUFFER_SIZE);

  NVIC->ISER[0] |= (1 << UART0_IRQn);
}


uint32_t bsp_uart_write(uint8_t* data, uint32_t size)
{
  uint32_t written = ringbuffer_push(uart0_tx_ringbuffer, data, size);
  if(written)
  {
    NVIC->ISER[0] &= ~(1 << UART0_IRQn);

    uint8_t c;
    while(!(UART0->FR & UART_FR_TXFF) &&
          !(ringbuffer_empty(&uart0_tx_ringbuffer)))
    {
      ringbuffer_pop(&uart0_tx_ringbuffer, &c, 1);
      UART0->DR = c;
    }

    NVIC->ISER[0] |= (1 << UART0_IRQn);
    UART0->IM |= UART_IM_TXIM;
  }

  return written;
}


uint32_t bsp_uart_read(uint8_t* data, uint32_t size)
{
  return 0;
}


void UART0_Handler(void)
{
  /*Read interrupt flags*/
  uint32_t status = UART0->MIS;
  /*Clear interrupt flags*/
  UART0->ICR |= status;

  uint8_t c;
  if(status & UART_MIS_RXMIS)
  {
    c = UART0->DR;
    ringbuffer_push(uart0_rx_ringbuffer, &c, 1);
  }
  else if(status & UART_MIS_TXMIS)
  {
    while(!(UART0->FR & UART_FR_TXFF) &&
          !(ringbuffer_empty(&uart0_tx_ringbuffer)))
    {
      ringbuffer_pop(&uart0_tx_ringbuffer, &c, 1);
      UART0->DR = c;
    }

    if(ringbuffer_empty(&uart0_tx_ringbuffer))
    {
      UART0->IM &= ~UART_IM_TXIM;
    }
  }
}
