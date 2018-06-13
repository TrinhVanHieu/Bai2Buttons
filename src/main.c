
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
	write_reg(GPIOC_MODER, 0x00050000u); /*init pin pc8 - pc9*/
	read_reg(GPIOA_MODER, GPIO_MODE_INPUT);
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
int a;
/*Buttons*/
void button (void)
{
	int check = read_reg(GPIOA_IDR, 1);
	if (check == 1)
	{
		if (a == 1)
		{
			turn_on (LD4_PIN);
			a = 0;
		}
		else
		{
			turn_off(LD4_PIN);
			a = 1;
		}
	}
}
void main(void)
{
	/*enable clock*/
	enable_clock();
	/*init_pin*/
	init_pin();
	
  while(1)
  {
	button ();
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


