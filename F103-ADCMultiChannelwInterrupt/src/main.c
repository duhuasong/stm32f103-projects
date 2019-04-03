/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    27-March-2019
  * @brief   Reading 2 channel ADC with Interrupt without DMA
  * @brief	 A0 and A1 as Analog Input 0 and 1 respectively
  ******************************************************************************
*/

#include "stm32f10x.h"
#include "ADCLibrary.h"
#include "LCDLibrary.h"

volatile int channel = 0;
volatile int ch0 = 0;
volatile int ch1 = 0;

int main(void)
{
	LCDInitialize();
	LCDSetupDisplay();
	LCDSend2LinesOfStringWithDelay(0, "ADC0:", "ADC1:");

	ADCInitialize();

	// Select ADC Channels
	ADCChannelSelect(0);
	ADCChannelSelect(1);

	// Enable ADC Interrupt
	ADC1->CR1 |= ADC_CR1_EOCIE;
	NVIC_EnableIRQ(ADC1_2_IRQn);

	// Start ADC in continuous mode
	// ADC1->CR1 |= ADC_CR1_SCAN;
	ADC1->CR2 |= ADC_CR2_CONT;
	ADC1->CR2 |= ADC_CR2_ADON;

	while(1)
	{
		LCDSetCursorPosition(6, 0);
		LCDSendAString("    ");
		LCDSetCursorPosition(6, 0);
		LCDSendAnInteger(ch0, 4);
		LCDSetCursorPosition(6, 1);
		LCDSendAString("    ");
		LCDSetCursorPosition(6, 1);
		LCDSendAnInteger(ch1, 4);
	}
}

void ADC1_2_IRQHandler(void)
{
	if(ADC1->SR & ADC_SR_EOC)
	{
		if(channel == 2) channel = 0;
		if(channel == 0)
		{
			// Before clearing interrupt flag(with reading DR), i changed the reading ADC channel
			ADC1->SQR3 = channel;
			ch1 = ADC1->DR;
		}
		if(channel == 1)
		{
			// Before clearing interrupt flag(with reading DR), i changed the reading ADC channel
			ADC1->SQR3 = channel;
			ch0 = ADC1->DR;
		}
		channel++;
	}
}
