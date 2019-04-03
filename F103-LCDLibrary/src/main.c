/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "LCDLibrary.h"

int main(void)
{
	LCDInitialize();
	LCDSetupDisplay();
	/*
	LCDSendAString("Integer: ");
	LCDSendAnInteger(100, 3);
	LCDSendAnInstruction(LCDInstruction_GoToNextLine);
	LCDSendAString("Float: ");
	LCDSendAFloatNumber(256.3, 7);
	*/

	LCDSetCursorPosition(2, 0);
	LCDSendAString("***TUGRA***");
	LCDSetCursorPosition(2, 1);
	LCDSendAString("***TALHA***");
}

