/*
 * ADCLibrary.h
 *
 *  Created on: 25 Mar 2019
 *      Author: Mustafa Kabakci
 */

#ifndef ADCLIBRARY_H_
#define ADCLIBRARY_H_

static int channelCount;

void ADCInitialize()
{
	// Select Clock Source
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;		// Enable ADC clock source
	RCC->CR |= RCC_CR_HSION;
	while((RCC->CR & RCC_CR_HSIRDY) == 0){} // Make sure HSI is ready.

	ADC1->CR2 |= ADC_CR2_ADON | ADC_CR2_CAL;
	while((ADC1->CR2 & ADC_CR2_CAL) == 1){} // wait until the calibration is completed and reseted
}

void ADCChannelSelect(uint8_t channel)
{
	// Select channel
	if(channel < 10)
	{
		ADC1->SMPR2 = 7 << channel * 3;
	}
	else if(channel < 18)
	{
		ADC1->SMPR1 = 7 << channel * 3;
	}

	// Set to convert the channel's conversion sequence
	if(channelCount < 7)
	{
		ADC1->SQR3 = channel << channelCount * 5;
	}
	else if(channelCount < 13)
	{
		ADC1->SQR2 = channel << channelCount * 5;
	}
	else if(channelCount < 17)
	{
		ADC1->SQR1 = channel << channelCount * 5;
	}

	channelCount++;
/*	if(channelCount > 1)
	{
		ADC1->SQR1 = (channelCount - 1) << 20;
	}
*/
}

#endif /* ADCLIBRARY_H_ */
