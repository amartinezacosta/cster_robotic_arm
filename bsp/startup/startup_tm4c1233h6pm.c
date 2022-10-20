#include <TM4C123.h>

/*Cortex M4 Exceptions*/
/*Exceptions 1-15*/
void Reset_Handler(void);
void NMI_Handler(void)              __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler(void)        __attribute__ ((weak));
void MemManage_Handler(void)        __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler(void)         __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void SecureFault_Handler(void)      __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler(void)              __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler(void)         __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler(void)           __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler(void)          __attribute__ ((weak, alias("Default_Handler")));

/*TM4C1233H6PM Exceptions*/
/*Exceptions 16-24*/
void GPIOA_Handler(void)            __attribute__ ((weak, alias("Default_Handler")));
void GPIOB_Handler(void)            __attribute__ ((weak, alias("Default_Handler")));
void GPIOC_Handler(void)            __attribute__ ((weak, alias("Default_Handler")));
void GPIOD_Handler(void)            __attribute__ ((weak, alias("Default_Handler")));
void GPIOE_Handler(void)            __attribute__ ((weak, alias("Default_Handler")));
void UART0_Handler(void)            __attribute__ ((weak, alias("Default_Handler")));
void UART1_Handler(void)            __attribute__ ((weak, alias("Default_Handler")));
void SSI0_Handler(void)             __attribute__ ((weak, alias("Default_Handler")));
void I2C0_Handler(void)             __attribute__ ((weak, alias("Default_Handler")));
/*Exceptions 30-42*/
void ADC0Seq0_Handler(void)         __attribute__ ((weak, alias("Default_Handler")));
void ADC0Seq1_Handler(void)         __attribute__ ((weak, alias("Default_Handler")));
void ADC0Seq2_Handler(void)         __attribute__ ((weak, alias("Default_Handler")));
void ADC0Seq3_Handler(void)         __attribute__ ((weak, alias("Default_Handler")));
void WDT_Handler(void)              __attribute__ ((weak, alias("Default_Handler")));
void TIMER16_0A_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIMER16_0B_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIMER16_1A_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIMER16_1B_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIMER16_2A_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIMER16_2B_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void ACOMP0_Handler(void)           __attribute__ ((weak, alias("Default_Handler")));
void ACOMP1_Handler(void)           __attribute__ ((weak, alias("Default_Handler")));
/*Exceptions 44-46*/
void SysCtl_Handler(void)           __attribute__ ((weak, alias("Default_Handler")));
void Flash_Handler(void)            __attribute__ ((weak, alias("Default_Handler")));
void GPIOF_Handler(void)            __attribute__ ((weak, alias("Default_Handler")));
/*Exceptions 49-53*/
void UART2_Handler(void)            __attribute__ ((weak, alias("Default_Handler")));
void SSI1_Handler(void)             __attribute__ ((weak, alias("Default_Handler")));
void TIMER16_3A_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIMER16_3B_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void I2C1_Handler(void)             __attribute__ ((weak, alias("Default_Handler")));
/*Exception 55*/
void CAN0_Handler(void)             __attribute__ ((weak, alias("Default_Handler")));
/*Exception 59-60*/
void Hibernation_Handler(void)      __attribute__ ((weak, alias("Default_Handler")));
void USB_Handler(void)              __attribute__ ((weak, alias("Default_Handler")));
/*Exception 62-67*/
void UDMASoft_Handler(void)         __attribute__ ((weak, alias("Default_Handler")));
void UDMAError_Handler(void)        __attribute__ ((weak, alias("Default_Handler")));
void ADC1Seq0_Handler(void)         __attribute__ ((weak, alias("Default_Handler")));
void ADC1Seq1_Handler(void)         __attribute__ ((weak, alias("Default_Handler")));
void ADC1Seq2_Handler(void)         __attribute__ ((weak, alias("Default_Handler")));
void ADC1Seq3_Handler(void)         __attribute__ ((weak, alias("Default_Handler")));
/*Exception 74-79*/
void SSI2_Handler(void)             __attribute__ ((weak, alias("Default_Handler")));
void SSI3_Handler(void)             __attribute__ ((weak, alias("Default_Handler")));
void UART3_Handler(void)            __attribute__ ((weak, alias("Default_Handler")));
void UART4_Handler(void)            __attribute__ ((weak, alias("Default_Handler")));
void UART5_Handler(void)            __attribute__ ((weak, alias("Default_Handler")));
void UART6_Handler(void)            __attribute__ ((weak, alias("Default_Handler")));
void UART7_Handler(void)            __attribute__ ((weak, alias("Default_Handler")));
/*Exception 84-87*/
void I2C2_Handler(void)             __attribute__ ((weak, alias("Default_Handler")));
void I2C3_Handler(void)             __attribute__ ((weak, alias("Default_Handler")));
void TIMER16_4A_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIMER16_4B_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
/*Exception 108-122*/
void TIMER16_5A_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIMER16_5B_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIMER64_0A_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIMER64_0B_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIMER64_1A_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIMER64_1B_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIMER64_2A_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIMER64_2B_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIMER64_3A_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIMER64_3B_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIMER64_4A_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIMER64_4B_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIMER64_5A_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIMER64_5B_Handler(void)       __attribute__ ((weak, alias("Default_Handler")));
void System_Handler(void)           __attribute__ ((weak, alias("Default_Handler")));

/*Data section extern symbols*/
extern uint32_t __etext;
extern uint32_t __data_start__;
extern uint32_t __data_end__;

/*BSS section extern symbols*/
extern uint32_t __bss_start__;
extern uint32_t __bss_end__;

extern int main(void);
extern void(__StackTop)(void);

void(*__vector_table[])(void) __attribute((section(".vector_table"))) = 
{
  /*Cortex M4F Exceptions*/
  __StackTop,           /*0 Initial Stack Pointer*/           
  Reset_Handler,        /*1 Reset Handler*/
  NMI_Handler,          /*2 NMI Handler*/
  HardFault_Handler,    /*3 HardFault Handler*/
  MemManage_Handler,    /*4 MemManage Handler*/
  BusFault_Handler,     /*5 BusFault Handler*/
  UsageFault_Handler,   /*6 UsageFault Handler*/
  0,                    /*7 Reserved*/
  0,                    /*8 Reserved*/
  0,                    /*9 Reserved*/
  0,                    /*10 Reserved*/ 
  SVC_Handler,          /*11 Reserved*/
  DebugMon_Handler,     /*12 Debug Monitor Handler*/
  0,                    /*13 Reserved*/
  PendSV_Handler,       /*14 PendSV Handler*/
  SysTick_Handler,      /*15 SysTick Handler*/ 

  /*TM4C1233H6PM Exceptions*/
  GPIOA_Handler,        /*16 GPIOA*/
  GPIOB_Handler,        /*17 GPIOB*/
  GPIOC_Handler,        /*18 GPIOC*/
  GPIOD_Handler,        /*19 GPIOD*/
  GPIOE_Handler,        /*20 GPIOE*/
  UART0_Handler,        /*21 UART0*/
  UART1_Handler,        /*22 UART1*/
  SSI0_Handler,         /*23 SSI0*/
  I2C0_Handler,         /*24 I2C0*/
  0,                    /*25 Reserved*/
  0,                    /*26 Reserved*/
  0,                    /*27 Reserved*/
  0,                    /*28 Reserved*/
  0,                    /*29 Reserved*/
  ADC0Seq0_Handler,     /*30 ADC0 Sequence 0*/
  ADC0Seq1_Handler,     /*31 ADC0 Sequence 1*/
  ADC0Seq2_Handler,     /*32 ADC0 Sequence 2*/
  ADC0Seq3_Handler,     /*33 ADC0 Sequence 3*/  
  WDT_Handler,          /*34 Watch Dog Timer*/
  TIMER16_0A_Handler,   /*35 16/32-bit Timer 0A*/
  TIMER16_0B_Handler,   /*36 16/32-bit Timer 0B*/
  TIMER16_1A_Handler,   /*37 16/32-bit Timer 1A*/
  TIMER16_1B_Handler,   /*38 16/32-bit Timer 1B*/  
  TIMER16_2A_Handler,   /*39 16/32-bit Timer 2A*/
  TIMER16_2B_Handler,   /*40 16/32-bit Timer 2B*/
  ACOMP0_Handler,       /*41 Analog Comparator 0*/
  ACOMP1_Handler,       /*42 Analog Comparator 1*/
  0,                    /*43 Reserved*/
  SysCtl_Handler,       /*44 System Control*/
  Flash_Handler,        /*45 Flash Memory Control and EEPROM Control*/
  GPIOF_Handler,        /*46 GPIOF*/
  0,                    /*47 Reserved*/
  0,                    /*48 Reserved*/
  UART2_Handler,        /*49 UART2*/
  SSI1_Handler,         /*50 SSI1*/
  TIMER16_3A_Handler,   /*51 16/32-bit Timer 3A*/
  TIMER16_3B_Handler,   /*52 16/32-bit Timer 3B*/  
  I2C1_Handler,         /*53 I2C1*/
  0,                    /*54 Reserved*/
  CAN0_Handler,         /*55 CAN0*/
  0,                    /*56 Reserved*/
  0,                    /*57 Reserved*/
  0,                    /*58 Reserved*/
  Hibernation_Handler,  /*59 Hibernation*/
  USB_Handler,          /*60 USB*/
  0,                    /*61 Reserved*/
  UDMASoft_Handler,     /*62 uDMA Software*/
  UDMAError_Handler,    /*63 uDMA Error*/
  ADC1Seq0_Handler,     /*64 ADC 1 Sequence 0*/
  ADC1Seq1_Handler,     /*65 ADC 1 Sequence 1*/
  ADC1Seq2_Handler,     /*66 ADC 1 Sequence 2*/
  ADC1Seq3_Handler,     /*67 ADC 1 Sequence 3*/
  0,                    /*68 Reserved*/
  0,                    /*69 Reserved*/
  0,                    /*70 Reserved*/
  0,                    /*71 Reserved*/ 
  0,                    /*72 Reserved*/
  SSI2_Handler,         /*73 SSI2*/
  SSI3_Handler,         /*74 SSI3*/
  UART3_Handler,        /*75 UART3*/
  UART4_Handler,        /*76 UART4*/
  UART5_Handler,        /*77 UART5*/
  UART6_Handler,        /*78 UART6*/
  UART7_Handler,        /*79 UART7*/
  0,                    /*80 Reserved*/
  0,                    /*81 Reserved*/
  0,                    /*82 Reserved*/
  0,                    /*83 Reserved*/
  I2C2_Handler,         /*84 I2C2*/
  I2C3_Handler,         /*85 I2C3*/
  TIMER16_4A_Handler,   /*86 16/32-bit Timer 4A*/
  TIMER16_4B_Handler,   /*87 16/32-bit Timer 4B*/
  0,                    /*88 Reserved*/
  0,                    /*89 Reserved*/
  0,                    /*90 Reserved*/
  0,                    /*91 Reserved*/
  0,                    /*92 Reserved*/
  0,                    /*93 Reserved*/
  0,                    /*94 Reserved*/
  0,                    /*95 Reserved*/
  0,                    /*96 Reserved*/
  0,                    /*97 Reserved*/
  0,                    /*98 Reserved*/
  0,                    /*99 Reserved*/
  0,                    /*100 Reserved*/
  0,                    /*101 Reserved*/
  0,                    /*102 Reserved*/
  0,                    /*103 Reserved*/
  0,                    /*104 Reserved*/
  0,                    /*105 Reserved*/
  0,                    /*106 Reserved*/
  0,                    /*107 Reserved*/
  TIMER16_5A_Handler,   /*108 16/32-bit Timer 5A*/
  TIMER16_5B_Handler,   /*109 16/32-bit Timer 5B*/
  TIMER64_0A_Handler,   /*110 32/64-bit Timer 0A*/
  TIMER64_0B_Handler,   /*111 32/64-bit Timer 0B*/
  TIMER64_1A_Handler,   /*112 32/64-bit Timer 1A*/
  TIMER64_1B_Handler,   /*113 32/64-bit Timer 1B*/
  TIMER64_2A_Handler,   /*114 32/64-bit Timer 2A*/
  TIMER64_2B_Handler,   /*115 32/64-bit Timer 2B*/
  TIMER64_3A_Handler,   /*116 32/64-bit Timer 3A*/
  TIMER64_3B_Handler,   /*117 32/64-bit Timer 3B*/
  TIMER64_4A_Handler,   /*118 32/64-bit Timer 4A*/
  TIMER64_4B_Handler,   /*119 32/64-bit Timer 4B*/
  TIMER64_5A_Handler,   /*120 32/64-bit Timer 5A*/
  TIMER64_5B_Handler,   /*121 32/64-bit Timer 5B*/
  System_Handler,       /*122 System Exception*/
  0,                    /*123 Reserved*/
  0,                    /*124 Reserved*/
  0,                    /*125 Reserved*/
  0,                    /*126 Reserved*/
  0,                    /*127 Reserved*/
  0,                    /*128 Reserved*/
  0,                    /*129 Reserved*/
  0,                    /*130 Reserved*/
  0,                    /*131 Reserved*/
  0,                    /*132 Reserved*/
  0,                    /*133 Reserved*/
  0,                    /*134 Reserved*/
  0,                    /*135 Reserved*/
  0,                    /*136 Reserved*/
  0,                    /*137 Reserved*/
  0,                    /*138 Reserved*/
  0,                    /*139 Reserved*/
  0,                    /*140 Reserved*/
  0,                    /*141 Reserved*/
  0,                    /*142 Reserved*/
  0,                    /*143 Reserved*/
  0,                    /*144 Reserved*/
  0,                    /*145 Reserved*/
  0,                    /*146 Reserved*/
  0,                    /*147 Reserved*/
  0,                    /*148 Reserved*/
  0,                    /*149 Reserved*/
  0,                    /*150 Reserved*/
  0,                    /*151 Reserved*/
  0,                    /*152 Reserved*/
  0,                    /*153 Reserved*/
  0,                    /*154 Reserved*/  
};

void HardFault_debug(uint32_t *stack)
{
  if(CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)
  {
     /*Break here to analyze stack*/
     __asm("bkpt 1");
  }
  
  /*TODO: Visualize this fault?*/

  /*Reset the system*/
}

__attribute__((naked, noreturn)) void HardFault_Handler(void)
{
  __asm volatile
  (
     "tst lr, #4         \n"
     "ite eq             \n"
     "mrseq r0, msp      \n"
     "mrsne r0, psp      \n"
     "b HardFault_debug  \n"
  );
}

void Default_Handler(void)
{

}

__attribute__((noreturn)) void Reset_Handler(void) 
{
  /*Copy data section from FLASH to SRAM*/
  uint32_t *psrc = &__etext;
  uint32_t *pdes = &__data_start__;
  while(pdes < &__data_end__)
  {
      *pdes++ = *psrc++;
  }

  /*Initalize BSS section to 0*/
  pdes = &__bss_start__;
  while(pdes < &__bss_end__)
  {
      *pdes++ = 0;
  }

  /*Enable floating point unit*/
  SCB->CPACR = ((0x03 << 22) | (0x03 << 20)); 

  /*Initialize TM4C1233H6PM system*/
  /*1. Bypass the PLL and system clock divider*/
  SYSCTL->RCC2 |= SYSCTL_RCC2_USERCC2 | SYSCTL_RCC2_BYPASS2;
  SYSCTL->RCC &= ~SYSCTL_RCC_USESYSDIV;

  /*2. Select the crystal value (XTAL) and oscillator source,
       and clear the PWRDN bit in RCC/RCC2*/
  SYSCTL->RCC |= SYSCTL_RCC_XTAL_16MHZ;
  SYSCTL->RCC2 |= SYSCTL_RCC2_OSCSRC2_MO;
  SYSCTL->RCC2 &= ~SYSCTL_RCC2_PWRDN2;

  /*3. Select the desired system divider (SYSDIV) in RCC/RCC2
       and set the USESYS bit in RCC.*/
  SYSCTL->RCC2 |= SYSCTL_RCC2_DIV400 | 
                  (SYSCTL_RCC2_SYSDIV2_M & 0x02);
  SYSCTL->RCC2 &= ~SYSCTL_RCC2_SYSDIV2LSB;
  SYSCTL->RCC |= SYSCTL_RCC_USESYSDIV;  

  /*4. Wait for the PLL to lock by polling the PLLRIS bit 
       in the RIS register*/
  while(!(SYSCTL->RIS & SYSCTL_RIS_PLLLRIS));

  /*5. Enable the PLL by clearing the BYPASS bit*/
  SYSCTL->RCC2 &= ~SYSCTL_RCC2_BYPASS2;

  /*Call main application*/
  main();

  /*Do not return*/
  for(;;);
}


