
#include "hw_stm32f030_mini.h"

void delay(unsigned int timeout)
{
   unsigned int t1, t2;
    for (t1 = 0; t1 < timeout; t1++)
    {
        for (t2 = 0; t2 < 0xFFF; t2++)
        {
          asm(" nop");
        }
    }
}

/*enable clock*/
void enable_clock(void)
{
	/*GPIOC*/
	unsigned long int tmpreg; \
    tmpreg = read_reg(RCC_AHBENR, ~RCC_AHBENR_IOPCEN);\
    tmpreg = tmpreg | RCC_AHBENR_IOPCEN; \
    write_reg(RCC_AHBENR, tmpreg);\
    delay(10); \
	/*GPIOA*/
	unsigned long int tmpreg1; \
    tmpreg1 = read_reg(RCC_AHBENR, ~RCC_AHBENR_IOPAEN);\
    tmpreg1 = tmpreg1 | RCC_AHBENR_IOPAEN; \
    write_reg(RCC_AHBENR, tmpreg1);\
    delay(10); \
	
}
/*set mode GC8 - GC9*/
void init_pin (void)
{
	/*init Pc8 Pc9*/
	unsigned long int tmpreg; 
    tmpreg = read_reg(GPIOC_MODER, ~(0x0fu << 16)); //reset port  pc9 pc8
    tmpreg = tmpreg | (0x05u << 16); 
    write_reg(GPIOC_MODER, tmpreg);
	/*init buttons PA0*/
    tmpreg = read_reg(GPIOA_MODER, ~(0x03u << 0)); //reset PA0
    tmpreg = tmpreg | (GPIO_MODE_INPUT << 0); 
    write_reg(GPIOA_MODER, tmpreg);
}

/*ON - OFF led*/
void turn_on (unsigned char pin)
{
	write_reg(GPIOC_OBSRR, 1 << pin);
}
void turn_off (unsigned char pin)
{
	write_reg(GPIOC_OBSRR, 1 << (pin + 16));
}

void main(void)
{
	/*enable clock*/
	enable_clock();
	/*init_pin*/
	init_pin();
	unsigned int buttons;
	unsigned int state = 0;
  while(1)
  {
	buttons = read_reg (GPIOA_IDR, 1 << 0);
	if (1 == buttons)
	{
		if (1 == state) 
		{
			turn_on(LD3_PIN);
			state = 0;
		}
		else 
		{
			turn_off(LD3_PIN);
			state = 1;
		}
	}
  }
}

void Reserved_IRQHandler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void NMI_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void HardFault_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void SVC_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void PendSV_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void SysTick_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}


