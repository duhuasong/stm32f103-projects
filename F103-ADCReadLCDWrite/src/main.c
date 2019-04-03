/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    22-March-2019
  * @brief   Single Channel Analog Read With Interrupt and Print It to LCD
  ******************************************************************************
*/


#include "stm32f10x.h"
#include "LCDLibrary.h"

int readingVal = 0;

int main(void)
{
	// LCD Initialize
	LCDInitialize();
	LCDSetupDisplay();

	// Set A1 pin as Analog Input
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN;
	//GPIOA->CRL &= ~(GPIO_CRL_CNF1_0);
	//GPIOA->CRL &= ~(GPIO_CRL_CNF1_1);
	//GPIOA->CRL |= GPIO_CRL_CNF1_1;

	// Enable ADC Clock
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	RCC->CR |= RCC_CR_HSION;
	while((RCC->CR & RCC_CR_HSIRDY) == 0);

	// Enable ADC Interrupt
	ADC1->CR1 |= ADC_CR1_EOCIE;
	NVIC_EnableIRQ(ADC1_2_IRQn);

	// Set channel 1(A1 pin) to read
	ADC1->SMPR2 |= ADC_SMPR2_SMP1_0 | ADC_SMPR2_SMP1_1 | ADC_SMPR2_SMP1_2;
	// Set channel 1 to be first reading channel
	ADC1->SQR3 = 1;

	// Set mode as continuous
	ADC1->CR2 |= ADC_CR2_ADON | ADC_CR2_CONT;
	timeDelay(1000000);

	// Calibrate ADC
	ADC1->CR2 |= ADC_CR2_CAL;
	while((ADC1->CR2 & ADC_CR2_CAL) == 1);

	// According to reference, 2nd time to start ADC
	ADC1->CR2 |= ADC_CR2_ADON;

	while(1)
	{
		// Write reading ADC value to LCD Display
		LCDSendAnInstruction(LCDInstruction_ClearDisplay);
		LCDSendAnInteger(readingVal, 4);

		timeDelay(1000000);
	}
}

// Reading ADC value from data register at each interrupt
void ADC1_2_IRQHandler(void)
{
	if(ADC1->SR & ADC_SR_EOC)
	{
		readingVal = ADC1->DR;  // With reading DR, IF is cleared.(reference manual)
	}
}

