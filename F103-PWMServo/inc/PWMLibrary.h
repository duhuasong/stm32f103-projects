/*
 * PWMLibrary.h
 *
 *  Created on: 25 Mar 2019
 *      Author: muka
 */

#ifndef PWMLIBRARY_H_
#define PWMLIBRARY_H_

void PWMChannel4SetParams(int prescaler, int period, int duty_cycle)
{
	// Timer Settings
	TIM1->PSC = prescaler;
	TIM1->ARR = period;
	TIM1->CCR4 = duty_cycle;
}

void PWMInitialize(int prescaler, int period, int duty_cycle)
{
	// Enable TIM1 and GPIOA RCC
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

	// GPIO Settings A11 Alternate Function Output
	GPIOA->CRH |= GPIO_CRH_MODE11_0 | GPIO_CRH_MODE11_1 | GPIO_CRH_CNF11_1;	// Alt. Func. PP
	GPIOA->CRH &= ~(GPIO_CRH_CNF11_0);

	PWMChannel4SetParams(prescaler, period, duty_cycle);
	TIM1->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4PE;
	TIM1->CCER |= TIM_CCER_CC4E;
	TIM1->EGR |= TIM_EGR_UG;
	TIM1->CR1 |= TIM_CR1_CEN | TIM_CR1_ARPE;
	TIM1->BDTR |= TIM_BDTR_MOE;
}



#endif /* PWMLIBRARY_H_ */
