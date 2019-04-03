/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f10x.h"
			

int main(void)
{
	// RCC - enable clock for a1 and b1
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

	// setup control regs for LED output
	GPIOA->CRL |= GPIO_CRL_MODE1_0;
	GPIOA->CRL |= GPIO_CRL_MODE1_1;
	GPIOA->CRL &= ~(GPIO_CRL_CNF1_0);
	GPIOA->CRL &= ~(GPIO_CRL_CNF1_1);

	// setup control regs for push button
	GPIOB->CRL &= ~(GPIO_CRL_CNF1_0);
	GPIOB->CRL |= GPIO_CRL_CNF1_1;


	// initialize button pressed variable
	volatile char buttonPressed = 0;
	// initialize button pressed confidence level
	volatile int buttonPressedConfidenceLevel = 0;
	// initialize button released confidence level
	volatile int buttonReleasedConfidenceLevel = 0;
	// initialize confidence threshold
	volatile int confidenceThreshold = 200;
	// LED lit state
	volatile char LEDState = 0;

	while(1)
	{
		// if the button is pressed idr reg
		if(GPIOB->IDR & GPIO_IDR_IDR1)
		{
			if(buttonPressed == 0)
			{
				if(buttonPressedConfidenceLevel > confidenceThreshold)
				{
					// toggle LEDs
					if(LEDState == 0)
					{
						LEDState = 1;
						GPIOA->BSRR |= GPIO_BSRR_BS1;
					}
					else
					{
						LEDState = 0;
						GPIOA->BSRR |= GPIO_BSRR_BR1;
					}
					// update the button pressed variable to 1
					buttonPressed = 1;
				}
				else
				{
					// increase the button pressed confidence
					buttonPressedConfidenceLevel++;
					buttonReleasedConfidenceLevel = 0;
				}
			}
		}
		else
		{
			if(buttonPressed == 1)
			{
				// once the button release confidence level had been achieved
				if(buttonReleasedConfidenceLevel > confidenceThreshold)
				{
					// update the button pressed variable to 0
					buttonPressed = 0;
				}
				else
				{
					// increase the button released confidence level
					buttonReleasedConfidenceLevel++;
					buttonPressedConfidenceLevel = 0;
				}
			}
		}

	}
}
