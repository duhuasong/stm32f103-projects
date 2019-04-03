/**
  ******************************************************************************
  * @file    main.c
  * @author  Mustafa Kabakci
  * @version V1.0
  * @date    25-March-2019
  * @brief   PWM Controlled w/Potentiometer
  ******************************************************************************
*/

#include <stdio.h>
#include "stm32f10x.h"
#include "LCDLibrary.h"
#include "ADCLibrary.h"
#include "PWMLibrary.h"


int main(void)
{
	LCDInitialize();
	LCDSetupDisplay();

	ADCInitialize();
	ADCChannelSelect(0);

	// 1ms -90 | 1.5ms  0 | 2ms +90
	PWMInitialize(1999, 719, 899);

	LCDSend2LinesOfStringWithDelay(0, "ADC:", "Count:");
	timeDelay(100000);

	int pot = 0;

	while(1)
	{
		// Read 12 bit ADC Data
		ADC1->CR2 |= ADC_CR2_ADON;
		while((ADC1->SR & ADC_SR_EOC) == 0){}; // Wait for the end of conversion
		pot = ADC1->DR;
		LCDSetCursorPosition(5, 0);
		LCDSendAnInteger(pot, 5);
		pot = (pot * 54) / 4096;
		pot = pot + 36;
		//LCDSetCursorPosition(7, 1);
		//LCDSendAnInteger(TIM1->CNT, 5);
		//TIM1->CCR4 = ADC1->DR;
		/*if(TIM1->SR & TIM_SR_UIF)
		{
			secondsCounter++;
			LCDSetCursorPosition(7, 1);
			LCDSendAnInteger(secondsCounter, 5);
			TIM1->SR &= ~TIM_SR_UIF;
		}*/
		//timeDelay(100000);

		// 1ms -90 | 1.5ms  0 | 2ms +90
		// 720 ----> 20ms
		// 1ms ----> 36
		// 1.5ms --> 54
		// 2ms ----> 72

		PWMChannel4SetParams(1999, 719, pot);
		//timeDelay(7200000);
		//PWMChannel4SetParams(1999, 719, 90);
		//timeDelay(7200000);
	}
}
