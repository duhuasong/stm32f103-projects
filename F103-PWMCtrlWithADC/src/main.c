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


int main(void)
{
	LCDInitialize();
	LCDSetupDisplay();

	ADCInitialize();
	ADCChannelSelect(0);

	// Enable TIM1 and GPIOA RCC
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

	// GPIO Settings A11 Alternate Function Output
	GPIOA->CRH |= GPIO_CRH_MODE11_0 | GPIO_CRH_MODE11_1 | GPIO_CRH_CNF11_1;	// Alt. Func. PP
	GPIOA->CRH &= ~(GPIO_CRH_CNF11_0);

	// Timer Settings
	TIM1->PSC = 0;
	TIM1->ARR = 4095;

	TIM1->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4PE;
	TIM1->CCER |= TIM_CCER_CC4E;
	TIM1->EGR |= TIM_EGR_UG;
	TIM1->CR1 |= TIM_CR1_CEN | TIM_CR1_ARPE;
	TIM1->BDTR |= TIM_BDTR_MOE;

	timeDelay(100000);

	while(1)
	{
		// Read 12 bit ADC Data
		ADC1->CR2 |= ADC_CR2_ADON;
		while((ADC1->SR & ADC_SR_EOC) == 0){}; // Wait for the end of conversion

		LCDSetCursorPosition(0, 0);
		int pot = ADC1->DR;
		TIM1->CCR4 = pot;
		LCDSendAnInteger(ADC1->DR, 4);
		timeDelay(100000);
	}
}
