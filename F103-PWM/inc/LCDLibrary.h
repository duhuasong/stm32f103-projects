/*
 * 		@file   LCDLibrary.h
 *  	@date	19 Mar 2019
 *      @author	Mustafa Kabakci
 *      @brief	B12 ---> LCD D7
 *      @brief	B13 ---> LCD D6
 *      @brief	B14 ---> LCD D5
 *      @brief	B15 ---> LCD D4
 *      @brief	B6 ----> LCD Enable
 *      @brief	B7 ----> LCD Read/Write
 *      @brief	B8 ----> LCD Register Select
 */

#ifndef LCDLIBRARY_H_
#define LCDLIBRARY_H_

#include <stdio.h>

#define LCDD4Pin 15
#define LCDD4Port GPIOB

#define LCDD5Pin 14
#define LCDD5Port GPIOB

#define LCDD6Pin 13
#define LCDD6Port GPIOB

#define LCDD7Pin 12
#define LCDD7Port GPIOB

#define LCDEnablePin 6
#define LCDEnablePort GPIOB

#define LCDReadWritePin 7
#define LCDReadWritePort GPIOB

#define LCDRegisterSelectPin 8
#define LCDRegisterSelectPort GPIOB

#define LCDInstruction_NextLine 0b11000000
#define LCDInstruction_Set4BitMode_2LineDisplay 0b00101000
#define LCDInstruction_DisplayOn_CursorOff 0b00001100
#define LCDInstruction_ClearDisplay 0b00000001
#define LCDInstruction_IncPositionByOne 0b00000110

#define TimeDelayBeforeEnable 4000
#define TimeDelayBeforeDisable 8000

void timeDelay(uint32_t timeDelay)
{
	volatile int i;
	for(i = 0; i < timeDelay; i++)
	{

	}
}

void setPortAndPinForOutput(GPIO_TypeDef *port, int pinNumber)
{
	if(port == GPIOA) {
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	}
	if(port == GPIOB) {
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	}
	if(port == GPIOC) {
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	}
	if(pinNumber < 8)
	{
		port->CRL |= (1 << (pinNumber * 4));
		port->CRL |= (1 << ((pinNumber * 4) + 1));
		port->CRL &= ~(1 << ((pinNumber * 4) + 2));
		port->CRL &= ~(1 << ((pinNumber * 4) + 3));
	} else
	{
		port->CRH |= (1 << ((pinNumber - 8) * 4));
		port->CRH |= (1 << (((pinNumber - 8) * 4) + 1));
		port->CRH &= ~(1 << (((pinNumber - 8) * 4) + 2));
		port->CRH &= ~(1 << (((pinNumber - 8) * 4) + 3));
	}
}

void sendBitToPortAndPin(GPIO_TypeDef *port, int pinNumber, uint8_t bitState)
{
	if(bitState) {
		port->BSRR |= (1 << pinNumber);
	} else {
		port->BRR |= (1 << pinNumber);
	}
}

void LCDInitialize()
{
	setPortAndPinForOutput(LCDD4Port, LCDD4Pin);
	setPortAndPinForOutput(LCDD5Port, LCDD5Pin);
	setPortAndPinForOutput(LCDD6Port, LCDD6Pin);
	setPortAndPinForOutput(LCDD7Port, LCDD7Pin);
	setPortAndPinForOutput(LCDEnablePort, LCDEnablePin);
	setPortAndPinForOutput(LCDReadWritePort, LCDReadWritePin);
	setPortAndPinForOutput(LCDRegisterSelectPort, LCDRegisterSelectPin);
}

void LCDEnable()
{
	timeDelay(TimeDelayBeforeEnable);
	sendBitToPortAndPin(LCDEnablePort, LCDEnablePin, 1);
}

void LCDDisable()
{
	timeDelay(TimeDelayBeforeDisable);
	sendBitToPortAndPin(LCDEnablePort, LCDEnablePin, 0);
}

void LCDSetToWrite()
{
	sendBitToPortAndPin(LCDReadWritePort, LCDReadWritePin, 0);
}

void LCDSetToRead()
{
	sendBitToPortAndPin(LCDReadWritePort, LCDReadWritePin, 1);
}

void LCDInstructionMode()
{
	sendBitToPortAndPin(LCDRegisterSelectPort, LCDRegisterSelectPin, 0);
}

void LCDCharacterMode()
{
	sendBitToPortAndPin(LCDRegisterSelectPort, LCDRegisterSelectPin, 1);
}

void LCDSendAByteToTheLCDDataPins(char character)
{
	sendBitToPortAndPin(LCDD4Port, LCDD4Pin, character & 0b00010000);
	sendBitToPortAndPin(LCDD5Port, LCDD5Pin, character & 0b00100000);
	sendBitToPortAndPin(LCDD6Port, LCDD6Pin, character & 0b01000000);
	sendBitToPortAndPin(LCDD7Port, LCDD7Pin, character & 0b10000000);
	LCDDisable();
	sendBitToPortAndPin(LCDEnablePort, LCDEnablePin, 1);
	sendBitToPortAndPin(LCDD4Port, LCDD4Pin, character & 0b00000001);
	sendBitToPortAndPin(LCDD5Port, LCDD5Pin, character & 0b00000010);
	sendBitToPortAndPin(LCDD6Port, LCDD6Pin, character & 0b00000100);
	sendBitToPortAndPin(LCDD7Port, LCDD7Pin, character & 0b00001000);
	LCDDisable();

}

void LCDSendACharacter(char character)
{
	LCDSetToWrite();
	LCDCharacterMode();
	LCDEnable();
	LCDSendAByteToTheLCDDataPins(character);
}

void LCDSendAnInstruction(char character)
{
	LCDSetToWrite();
	LCDInstructionMode();
	LCDEnable();
	LCDSendAByteToTheLCDDataPins(character);
}

void LCDSendAString(char *StringOfCharacters)
{
	while(*StringOfCharacters)
	{
		LCDSendACharacter(*StringOfCharacters++);
	}
}

void LCDSetupDisplay()
{
	LCDSendAnInstruction(LCDInstruction_Set4BitMode_2LineDisplay);
	LCDSendAnInstruction(LCDInstruction_DisplayOn_CursorOff);
	LCDSendAnInstruction(LCDInstruction_IncPositionByOne);
	LCDSendAnInstruction(LCDInstruction_ClearDisplay);
}

void LCDSend2LinesOfStringWithDelay(int delay, char *StringOfCharactersLine1, char *StringOfCharactersLine2)
{
	timeDelay(TimeDelayBeforeEnable);
	LCDSendAnInstruction(LCDInstruction_ClearDisplay);
	LCDSendAString(StringOfCharactersLine1);
	LCDSendAnInstruction(LCDInstruction_NextLine);
	LCDSendAString(StringOfCharactersLine2);
}

void LCDSendAnInteger(int IntegerToBeDisplayed, uint8_t LengthOfDigits)
{
	char StringNumber[LengthOfDigits];
	sprintf(StringNumber, "%d", IntegerToBeDisplayed);
	LCDSendAString(StringNumber);
}

void LCDSendAFloatNumber(float FloatNumberToBeDisplayed, uint8_t LengthOfDigits)
{
	char StringNumber[LengthOfDigits];
	snprintf(StringNumber, LengthOfDigits, "%e", FloatNumberToBeDisplayed);
	LCDSendAString(StringNumber);
}

void LCDSetCursorPosition(int x, int y)
{
	int position = x + 40 * y;
	LCDSendAnInstruction(0x80 + position);
}


#endif /* LCDLIBRARY_H_ */
