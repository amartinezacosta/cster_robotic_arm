#include <bsp_tm4c123_motor.h>
#include <TM4C123.h>

static volatile int32_t encoder_count[3];

static void bsp_motor_pwm_init(void);
static void bsp_motor_gpio_init(void);
static void bsp_motor_gpio_power_init(void);
static void bsp_motor_sleep_init(void);

void bsp_motors_init(void)
{
  /*Wide Timer 0 and 1 enable clock*/
  SYSCTL->RCGCWTIMER |= SYSCTL_RCGCWTIMER_R0 | 
                        SYSCTL_RCGCWTIMER_R1 |
                        SYSCTL_RCGCWTIMER_R2;
  while( (!(SYSCTL->PRWTIMER & SYSCTL_PRWTIMER_R0)) && 
         (!(SYSCTL->PRWTIMER & SYSCTL_PRWTIMER_R1)) &&
         (!(SYSCTL->PRWTIMER & SYSCTL_PRWTIMER_R2)) );

  /*GPIO Port B, C and D enable clock*/
  SYSCTL->RCGCGPIO |= SYSCTL_RCGCGPIO_R1 | 
                      SYSCTL_RCGCGPIO_R2 |
                      SYSCTL_RCGCGPIO_R4 | 
                      SYSCTL_RCGCGPIO_R3 |
                      SYSCTL_RCGCGPIO_R5;
  while( (!(SYSCTL->PRGPIO & SYSCTL_PRGPIO_R1)) && 
         (!(SYSCTL->PRGPIO & SYSCTL_PRGPIO_R2)) &&
         (!(SYSCTL->PRGPIO & SYSCTL_PRGPIO_R3)) &&
         (!(SYSCTL->PRGPIO & SYSCTL_PRGPIO_R4)) &&
         (!(SYSCTL->PRGPIO & SYSCTL_PRGPIO_R5)));


  bsp_motor_sleep_init();
  bsp_motor_pwm_init();
  bsp_motor_gpio_init();
  bsp_motor_gpio_power_init();
}

static void bsp_motor_pwm_init(void)
{
    /*Select alternate function and set as digital pin*/
  GPIOC->AFSEL |= MOTOR_0_PWM_PINS | MOTOR_1_PWM_PINS;
  GPIOC->DEN |= MOTOR_0_PWM_PINS | MOTOR_1_PWM_PINS; 
  GPIOD->AFSEL |= MOTOR_2_PWM_PINS;
  GPIOD->DEN |= MOTOR_2_PWM_PINS;

  /*Select the peripheral alternate mux*/
  GPIOC->PCTL |=  GPIO_PCTL_PC4_WT0CCP0  | 
                  GPIO_PCTL_PC5_WT0CCP1  |
                  GPIO_PCTL_PC6_WT1CCP0  |
                  GPIO_PCTL_PC7_WT1CCP1;
  GPIOD->PCTL |=  GPIO_PCTL_PD0_WT2CCP0 |
                  GPIO_PCTL_PD1_WT2CCP1;

  /*Disable timers before making any changes*/
  WTIMER0->CTL &= ~TIMER_CTL_TAEN;
  WTIMER0->CTL &= ~TIMER_CTL_TBEN;
  WTIMER1->CTL &= ~TIMER_CTL_TAEN;
  WTIMER1->CTL &= ~TIMER_CTL_TBEN;
  WTIMER2->CTL &= ~TIMER_CTL_TAEN;
  WTIMER2->CTL &= ~TIMER_CTL_TBEN;

  /*Configure as 32-bit timer*/
  WTIMER0->CFG = TIMER_CFG_16_BIT;
  WTIMER1->CFG = TIMER_CFG_16_BIT;
  WTIMER2->CFG = TIMER_CFG_16_BIT;

  /*Set timer configuration*/
  /*WTIMER0 config*/
  WTIMER0->TAMR = TIMER_TAMR_TAAMS | TIMER_TAMR_TAMR_PERIOD;
  WTIMER0->TBMR = TIMER_TBMR_TBAMS | TIMER_TBMR_TBMR_PERIOD;
  WTIMER0->CTL |= (TIMER_CTL_TAPWML | TIMER_CTL_TBPWML);
  WTIMER0->TAILR = PWM_FREQUENCY;
  WTIMER0->TBILR = PWM_FREQUENCY;
  WTIMER0->TAMATCHR = 0;
  WTIMER0->TBMATCHR = 0;

  /*WTIMER1 config*/
  WTIMER1->TAMR = TIMER_TAMR_TAAMS | TIMER_TAMR_TAMR_PERIOD;
  WTIMER1->TBMR = TIMER_TBMR_TBAMS | TIMER_TBMR_TBMR_PERIOD;
  WTIMER1->CTL |= (TIMER_CTL_TAPWML | TIMER_CTL_TBPWML);
  WTIMER1->TAILR = PWM_FREQUENCY;
  WTIMER1->TBILR = PWM_FREQUENCY;
  WTIMER1->TAMATCHR = 0;
  WTIMER1->TBMATCHR = 0;

  /*WTIMER2 config*/
  WTIMER2->TAMR = TIMER_TAMR_TAAMS | TIMER_TAMR_TAMR_PERIOD;
  WTIMER2->TBMR = TIMER_TBMR_TBAMS | TIMER_TBMR_TBMR_PERIOD;
  WTIMER2->CTL |= (TIMER_CTL_TAPWML | TIMER_CTL_TBPWML);
  WTIMER2->TAILR = PWM_FREQUENCY;
  WTIMER2->TBILR = PWM_FREQUENCY;
  WTIMER2->TAMATCHR = 0;
  WTIMER2->TBMATCHR = 0;

  /*Enable timers*/
  WTIMER0->CTL |= TIMER_CTL_TAEN;
  WTIMER0->CTL |= TIMER_CTL_TBEN;
  WTIMER1->CTL |= TIMER_CTL_TAEN;
  WTIMER1->CTL |= TIMER_CTL_TBEN;
  WTIMER2->CTL |= TIMER_CTL_TAEN;
  WTIMER2->CTL |= TIMER_CTL_TBEN;
}

static void bsp_motor_gpio_init(void)
{
  /*Set GPIO direction*/
  GPIOB->DIR &= ~MOTORS_ENCODER_PINS;
  /*Enable digital pin mode*/
  GPIOB->DEN |= MOTORS_ENCODER_PINS;
  /*Disable interrupts*/
  GPIOB->IM &= ~MOTORS_ENCODER_PINS;
  /*Detect edge transitions*/
  GPIOB->IS &= ~MOTORS_ENCODER_PINS;
  /*Detect both edges*/
  GPIOB->IBE |= MOTORS_ENCODER_PINS;
  /*Clear any pending flags*/
  GPIOB->ICR |= MOTORS_ENCODER_PINS;
  /*Enable interrupts*/
  GPIOB->IM |= MOTORS_ENCODER_PINS;

  NVIC->ISER[0] |= (1 << 1);
}

static void bsp_motor_gpio_power_init(void)
{
  GPIOF->DIR |= BIT3;
  GPIOF->DEN |= BIT3;

  GPIOF->DATA &= ~BIT3;
}

static void bsp_motor_sleep_init(void)
{
  GPIOE->DIR |= (BIT2 | BIT3);
  GPIOE->DEN |= (BIT2 | BIT3);

  GPIOE->DATA |= (BIT2 | BIT3);
}

void bsp_motor_0_speed(uint32_t speed, motor_dir_t dir)
{
  if(speed > PWM_FREQUENCY) speed = PWM_FREQUENCY; 

  if(dir == CLOCKWISE)
  {
    WTIMER0->TAMATCHR = speed;
    WTIMER0->TBMATCHR = 0;
  }
  else
  {
    WTIMER0->TAMATCHR = 0;
    WTIMER0->TBMATCHR = speed;
  }
}

void bsp_motor_1_speed(uint32_t speed, motor_dir_t dir)
{
  if(speed > PWM_FREQUENCY) speed = PWM_FREQUENCY; 

  if(dir == CLOCKWISE)
  {
    WTIMER1->TAMATCHR = speed;
    WTIMER1->TBMATCHR = 0;
  }
  else
  {
    WTIMER1->TAMATCHR = 0;
    WTIMER1->TBMATCHR = speed;
  }
}

void bsp_motor_2_speed(uint32_t speed, motor_dir_t dir)
{
  if(speed > PWM_FREQUENCY) speed = PWM_FREQUENCY; 

  if(dir == CLOCKWISE)
  {
    WTIMER2->TAMATCHR = speed;
    WTIMER2->TBMATCHR = 0;
  }
  else
  {
    WTIMER2->TAMATCHR = 0;
    WTIMER2->TBMATCHR = speed;
  }
}

void bsp_motor_power_enable(void)
{
  GPIOF->DATA |= BIT3;

  /*TODO: delay for power supply voltage to settle*/
}

void bsp_motor_power_disable(void)
{
  GPIOF->DATA &= ~BIT3;

  /*TODO: delay for power supply voltage to settle*/
}

void bsp_motor_sleep_enable(void)
{
  GPIOE->DATA &= ~(BIT2 | BIT3);
}

void bsp_motor_sleep_disable(void)
{
  GPIOE->DATA |= (BIT2 | BIT3);
}

int32_t bsp_motor_0_encoder(void)
{
  __disable_irq();
  int32_t count = encoder_count[0];
  __enable_irq();
  
  return count;
}

int32_t bsp_motor_1_encoder(void)
{
  __disable_irq();
  int32_t count = encoder_count[1];
  __enable_irq();
  
  return count;
}

int32_t bsp_motor_2_encoder(void)
{
  __disable_irq();
  int32_t count = encoder_count[2];
  __enable_irq();
  
  return count;
}

/*Code found http://makeatronics.blogspot.com/2013/02/efficiently-reading-quadrature-with.html?m=1*/
void GPIOB_Handler(void)
{
  uint8_t mask = GPIOB->MIS;
  uint8_t data = GPIOB->DATA;

  static int8_t lookup_table[] = 
  {
    0,-1,1,0,
    1,0,0,-1,
    -1,0,0,1,
    0,1,-1,0
  };

  static uint8_t encoder_value[3] = {0};
  encoder_value[0] = encoder_value[0] << 2;
  encoder_value[1] = encoder_value[1] << 2;
  encoder_value[2] = encoder_value[2] << 2; 

  encoder_value[0] = encoder_value[0] | ((data & MOTORS_ENCODER_PINS) >> 2);
  encoder_value[1] = encoder_value[1] | ((data & MOTORS_ENCODER_PINS) >> 2);
  encoder_value[2] = encoder_value[2] | ((data & MOTORS_ENCODER_PINS) >> 2); 

  encoder_count[0] += lookup_table[encoder_value[0] & 0x0F];
  encoder_count[1] += lookup_table[encoder_value[1] & 0x0F];
  encoder_count[2] += lookup_table[encoder_value[2] & 0x0F];

  GPIOB->ICR |= mask;
}
