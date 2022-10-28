#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#define configMINIMAL_STACK_SIZE                128
#define configCPU_CLOCK_HZ                      80000000UL
#define configTICK_RATE_HZ                      1000UL
#define configMAX_PRIORITIES                    5
#define configUSE_PREEMPTION                    1
#define configUSE_16_BIT_TICKS                  0

/*Memory management configuration*/
#define configTOTAL_HEAP_SIZE                   4096

/*Interrupt nesting behaviour configuration*/
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    0
#define configKERNEL_INTERRUPT_PRIORITY         7

/*Hook functions*/
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0

/*Optional functions*/
#define INCLUDE_vTaskDelay                     1

#endif
