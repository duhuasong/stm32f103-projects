/**
  ******************************************************************************
  * @file    main.c
  * @author  Mustafa Kabakci
  * @version V1.0
  * @date    20-March-2019
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f10x.h"
#include "LCDLibrary.h"


int main(void)
{
	LCDInitialize();
	LCDSetupDisplay();

	// Select Clock Source
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;		// Enable ADC clock source
	RCC->CR |= RCC_CR_HSION;
	while((RCC->CR & RCC_CR_HSIRDY) == 0){} // Make sure HSI is ready.

	ADC1->CR2 |= ADC_CR2_ADON | ADC_CR2_CAL;
	while((ADC1->CR2 & ADC_CR2_CAL) == 1){} // wait until the calibration is completed and reseted

	ADC1->SQR3 |= ADC_SQR3_SQ1_4;			// Set to convert the channel 16 first
	ADC1->SMPR1 |= ADC_SMPR1_SMP16;
	ADC1->CR2 |= ADC_CR2_TSVREFE;			// Enable temp. sensor

	LCDSetCursorPosition(0,0);
	LCDSendAString("TEMPERATURE     ");
	while(1)
	{
		// Read 12 bit ADC Data
		ADC1->CR2 |= ADC_CR2_ADON;
		while((ADC1->SR & ADC_SR_EOC) == 0)
		{
			 // Wait for the end of conversion
		}

		float v25 = 1775.0;
		int temp = (int) ((v25 - ADC1->DR) / 4.3) + 25;

		LCDSetCursorPosition(3,1);
		LCDSendACharacter(223);
		LCDSendACharacter('C');
		LCDSetCursorPosition(0,1);
		LCDSendAnInteger(temp, 3);

		timeDelay(1000000);
	}
}
