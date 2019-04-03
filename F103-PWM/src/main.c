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
			

int main(void)
{
	// Enable TIM1 and GPIOA RCC
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;


	// GPIO Settings A11 Alternate Function Output
	GPIOA->CRH |= GPIO_CRH_MODE11_0 | GPIO_CRH_MODE11_1 | GPIO_CRH_CNF11_1;	// Alt. Func. PP
	GPIOA->CRH &= ~(GPIO_CRH_CNF11_0);

	// Timer Settings %50 duty-cycle
	TIM1->PSC = 0;
	TIM1->ARR = 100;
	TIM1->CCR4 = 50;

	TIM1->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4PE;
	TIM1->CCER |= TIM_CCER_CC4E;
	TIM1->EGR |= TIM_EGR_UG;
	TIM1->CR1 |= TIM_CR1_CEN | TIM_CR1_ARPE;
	TIM1->BDTR |= TIM_BDTR_MOE;

	while(1)
	{

	}
}
