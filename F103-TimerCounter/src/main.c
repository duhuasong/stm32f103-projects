/**
  ******************************************************************************
  * @file    main.c
  * @author  Mustafa Kabakci
  * @version V1.0
  * @date    22-March-2019
  * @brief   Introduction to Timers and Counters
  ******************************************************************************
*/

#include "stm32f10x.h"
#include "LCDLibrary.h"
			

int main(void)
{
	LCDInitialize();
	LCDSetupDisplay();

	// Enable TIM1 RCC
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	TIM1->PSC = 59999;
	TIM1->CR1 |= TIM_CR1_CEN;
	TIM1->ARR = 10000;

	LCDSend2LinesOfStringWithDelay(0, "Counter:", "Prescaler:");
	LCDSetCursorPosition(11,1);
	LCDSendAnInteger(TIM1->PSC, 5);

	while(1)
	{
		LCDSetCursorPosition(9,0);
		LCDSendAString("     ");
		LCDSetCursorPosition(9,0);
		LCDSendAnInteger(TIM1->CNT, 5);
		timeDelay(100000);
	}
}
