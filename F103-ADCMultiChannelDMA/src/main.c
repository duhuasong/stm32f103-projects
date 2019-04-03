/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    22-March-2019
  * @brief   Multiple Channel ADC with DMA
  *******************************************************************************
*/


#include "stm32f10x.h"
#include "LCDLibrary.h"

uint16_t readingVal[2] = {0};

int main(void)
{
	// LCD Initialize
	LCDInitialize();
	LCDSetupDisplay();

	// Set A1 pin as Analog Input
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN;
	//GPIOA->CRL &= ~(GPIO_CRL_CNF1_0);
	//GPIOA->CRL &= ~(GPIO_CRL_CNF1_1);
	//GPIOA->CRL &= ~(GPIO_CRL_CNF2_0);
	//GPIOA->CRL &= ~(GPIO_CRL_CNF2_1);

	// Enable ADC Clock
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	RCC->CR |= RCC_CR_HSION;
	while((RCC->CR & RCC_CR_HSIRDY) == 0);

	// Set channel 1 and 2 to read
	ADC1->SMPR2 |= ADC_SMPR2_SMP1_0 | ADC_SMPR2_SMP1_1 | ADC_SMPR2_SMP1_2;
	ADC1->SMPR2 |= ADC_SMPR2_SMP2_0 | ADC_SMPR2_SMP2_1 | ADC_SMPR2_SMP2_2;

	// Set channel's sequence
	ADC1->SQR1 = ADC_SQR1_L_0; 			// 2 channel
	ADC1->SQR3 = ADC_SQR3_SQ1_0;		// 1st read channel 1
	ADC1->SQR3 = ADC_SQR3_SQ2_1;		// 2nd read channel 2

	// Scan and DMA settings for ADC
	ADC1->CR1 |= ADC_CR1_SCAN;
	ADC1->CR2 |= ADC_CR2_DMA;

	// DMA Settings
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	DMA1_Channel1->CPAR = (uint32_t)(&(ADC1->DR));
	DMA1_Channel1->CMAR = (uint32_t)readingVal;
	DMA1_Channel1->CNDTR = 2;
	DMA1_Channel1->CCR |= DMA_CCR1_CIRC | DMA_CCR1_MINC | DMA_CCR1_PSIZE_0 | DMA_CCR1_MSIZE_0;
	DMA1_Channel1->CCR |= DMA_CCR1_EN;

	// Set mode as continuous
	ADC1->CR2 |= ADC_CR2_ADON | ADC_CR2_CONT;
	timeDelay(1000000);

	// According to reference, 2nd time to start ADC
	ADC1->CR2 |= ADC_CR2_ADON;

	// Calibrate ADC
	ADC1->CR2 |= ADC_CR2_CAL;
	while((ADC1->CR2 & ADC_CR2_CAL) == 1);

	while(1)
	{
		// Write reading ADC value to LCD Display
		LCDSendAnInstruction(LCDInstruction_ClearDisplay);
		LCDSetCursorPosition(0, 0);
		LCDSendAnInteger(readingVal[0], 4);
		LCDSetCursorPosition(0, 1);
		LCDSendAnInteger(readingVal[1], 4);
		timeDelay(1000000);
	}
}

