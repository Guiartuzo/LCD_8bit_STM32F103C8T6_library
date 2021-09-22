#include "myLcd.h"
#include "stm32f10x.h"                  

void LcdInitGpio8Bits(void)	
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN |RCC_APB2ENR_IOPCEN;
	GPIOA->CRL |= 0x33333333;
	GPIOA->CRH |= 0x44434444;
	GPIOB->CRL |= 0x33343444;
	GPIOC->CRH |= 0x44344444;
}

void LcdInitGpio4Bits(void)	
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN |RCC_APB2ENR_IOPCEN;
	GPIOA->CRL |= 0x33334444;
	GPIOA->CRH |= 0x44434444;
	GPIOB->CRL |= 0x33343444;
	GPIOC->CRH |= 0x44344444;
}

void LcdBegin8bit2lines(void)
{
	SystickDelayMs(500);
	
	LcdSendCommand(0x30);	
	SystickDelayMs(10);
	LcdSendCommand(0x30);
	SystickDelayMs(10);	
	LcdSendCommand(0x30);
	SystickDelayMs(10);	
	
	LcdSendCommand(0x38);	
	SystickDelayMs(10);		
	LcdSendCommand(0x0F);
}

void LcdBegin4bits1lines(void)
{
	SystickDelayMs(500);
	
	LcdSendCommand(0x03);	
	SystickDelayMs(10);
	LcdSendCommand(0x03);
	SystickDelayMs(10);	
	LcdSendCommand(0x03);
	SystickDelayMs(10);	
	LcdSendCommand(0x02);	
	SystickDelayMs(10);	
	
	LcdSendCommand(0x02);
	LcdSendCommand(0x08);
	
	LcdSendCommand(0x00);
	LcdSendCommand(0x01);
}

void LcdWriteString(char string[])
{
	int i = 0;
	while(string[i]!= '\0')
	{
		LcdSendData(string[i]);
		i++;
	}
}

void LcdSendCommand(unsigned char com)
{
	GPIOB->BSRR = GPIO_BSRR_BR5;
	GPIOB->BSRR = GPIO_BSRR_BR6;
	GPIOA->ODR = com;
	SystickDelayMs(1);
	GPIOA->BSRR = GPIO_BSRR_BR12;
	GPIOA->BSRR = GPIO_BSRR_BS12;
	SystickDelayMs(1);
	GPIOA->BSRR = GPIO_BSRR_BR12;
}	

void LcdSendData(unsigned char data)
{
	GPIOB->BSRR = GPIO_BSRR_BS5;
	GPIOB->BSRR = GPIO_BSRR_BR6;
	GPIOA->ODR =	data;
	GPIOA->BSRR = GPIO_BSRR_BR12;
	GPIOA->BSRR = GPIO_BSRR_BS12;
	SystickDelayMs(1);
	GPIOA->BSRR = GPIO_BSRR_BR12;
}

void LcdClearHome(void)
{
	LcdSendCommand(0x01);
	SystickDelayMs(10);
	LcdSendCommand(0x02);
}

void LcdEntryModeIncrement(void)
{
	LcdSendCommand(0x07);
}

void LcdWriteNibble(char data)
{
	GPIOB->BSRR = GPIO_BSRR_BS5;
	GPIOB->BSRR = GPIO_BSRR_BR6;
	GPIOA->BSRR = 0x00F00000;
	GPIOA->BSRR = data & 0x0F;
	GPIOA->BSRR = GPIO_BSRR_BR12;
	GPIOA->BSRR = GPIO_BSRR_BS12;
	SystickDelayMs(1);
	GPIOA->BSRR = GPIO_BSRR_BR12;
}

void LcdWriteString4Bits(char data)
{
	LcdWriteNibble(data & 0x0F);
	LcdWriteNibble(data <<4);
	SystickDelayMs(1);
}

void SystickDelayMs(int n)
{
	SysTick->LOAD = 9000 -1;
	SysTick->VAL = 0;
	SysTick->CTRL = SysTick_CTRL_ENABLE;
	
	for (int i = 0; i<n; i++)
	{
		while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG) == 0);
	}
	
	SysTick->CTRL = 0;
}