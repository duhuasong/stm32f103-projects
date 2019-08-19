/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   B0 button counter
  ******************************************************************************
*/


#include "stm32f10x.h"
#include "LCDLibrary.h"

volatile int i = 0;

void EXTI0_IRQHandler(void)
{
	if(EXTI->PR & EXTI_PR_PR0)
	{
		EXTI->PR |= EXTI_PR_PR0;
	}
	i++;
}

int main(void)
{
	// initialize lcd
	timeDelay(100000);
	LCDInitialize();
	LCDSetupDisplay();
	LCDSend2LinesOfStringWithDelay(0, "B 0:", "");

	// clock and gpio settings B0 and AF
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;
	GPIOB->CRL &= ~(GPIO_CRL_CNF0_0);
	GPIOB->CRL |= GPIO_CRL_CNF0_1;

	// interrupt settings
	EXTI->IMR |= EXTI_IMR_MR0;
	EXTI->RTSR |= EXTI_RTSR_TR0;
	AFIO->EXTICR[0] |= AFIO_EXTICR1_EXTI0_PB;
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_SetPriority(EXTI0_IRQn, 15);

	while(1)
	{
		LCDSetCursorPosition(5, 0);
		LCDSendAnInteger(i, 3);
	}
}
