/*
 * lcd.c - Controls a standard 16x2 LCD
 *
 *  Created on: Jul 1, 2014
 *      Author: Cuong T. Nguyen
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

#include "delay.h"
#include "lcd.h"

/*
 * LCD helper functions
 */

/*
 * Variable for indicating interfacing mode
 */
bool data8Bit = 0;


/*
 * Latch data by toggling the Enable pin
 */
void lcdEnable() {
	GPIOPinWrite(LCD_GPIO_CTL_BASE, E_PIN, E_PIN);
	delayUs(5);
	GPIOPinWrite(LCD_GPIO_CTL_BASE, E_PIN, ~E_PIN);
	delayUs(5);
}

/*
 * Write data to Data pins. Written data might be 4-bit or 8-bit
 * according to data8Bit variable
 */

void lcdWriteData(uint8_t ui8Data) {
	if (data8Bit) {
		GPIOPinWrite(LCD_GPIO_DATA_BASE, DATA_PINS, ui8Data);
		lcdEnable();
	}
	else {
		GPIOPinWrite(LCD_GPIO_DATA_BASE, DATA_PINS, ui8Data & 0xF0); //send the rest 4-bits
		lcdEnable();
		GPIOPinWrite(LCD_GPIO_DATA_BASE, DATA_PINS, (ui8Data & 0x0F) << 4); //send first 4-bits
		lcdEnable();
	}
}

/*
 * Send command to the LCD
 */

void lcdWriteCommand(uint8_t ui8Com) {
	GPIOPinWrite(LCD_GPIO_CTL_BASE, E_PIN, ~E_PIN);
	//GPIOPinWrite(LCD_GPIO_CTL_BASE, RW_PIN, ~RW_PIN);
	GPIOPinWrite(LCD_GPIO_CTL_BASE, RS_PIN, ~RS_PIN);
	lcdWriteData(ui8Com);
	delayMs(5);
}

/*
 * Write a char to the LCD at the current string
 */

void lcdWriteChar(char cChar) {
	GPIOPinWrite(LCD_GPIO_CTL_BASE, E_PIN, ~E_PIN);
	//GPIOPinWrite(LCD_GPIO_CTL_BASE, RW_PIN, ~RW_PIN);
	GPIOPinWrite(LCD_GPIO_CTL_BASE, RS_PIN, RS_PIN);
	lcdWriteData(cChar);
	delayUs(100);
}

/*
 * Write a string to the LCD
 */

void lcdWriteString(char * s) {
	while (*s) {
		lcdWriteChar(*s);
		s ++;
	}
}

/*
 * Clear display
 */

void lcdClear() {
	lcdWriteCommand(CLEAR_DISPLAY);
}

/*
 * Clear display and write a string
 */

void lcdClearAndWriteString(char * s) {
	lcdClear();
	lcdWriteString(s);
}

/*
 * Set cursor at the specified coordinate in which x is the column and y is the row
 */

void lcdGoToXY(uint8_t ui8X, uint8_t ui8Y) {
	uint8_t ui8Address;
	// Specify the address
	if (ui8Y == 0) {
		ui8Address = 0x00 + ui8X;
	}
	else {
		ui8Address = 0x40 + ui8X;
	}
	// Set the bit for cursor moving command
	ui8Address |= 0x80;
	lcdWriteCommand(ui8Address);
}

/*
 * LCD initialization function
 * Things to consider when initialize a characters LCD:
 *  _Function set:
 * 		+ Interface data: 4-bit (0) or 8-bit (1)
 * 		+ Number of line: 1 line (0) or 2 lines (1)
 * 		+ Character font: 5x7 dots (0) or 5x10 dots (1)
 *  _Display on/off control:
 *  	+ Display: off (0) or on (1)
 *  	+ Cursor: off (0) or on (1)
 *  	+ Cursor blink: off (0) or on (1)
 *  _Entry mode set:
 *  	+ Cursor move direction: decrement (0) or increment (1)
 *  	+ Accompanies display shift: off (0) or on (1)
 */

void lcdInit(uint8_t ui8FunctionSetOptions, uint8_t ui8EntryModeSetOptions, uint8_t ui8DisplayOptions) {

	SysCtlPeripheralEnable(LCD_GPIO_DATA_PERIPH);
	SysCtlPeripheralEnable(LCD_GPIO_CTL_PERIPH);

	HWREG(LCD_GPIO_DATA_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(LCD_GPIO_DATA_BASE + GPIO_O_CR) |= 0x80;

	GPIOPinTypeGPIOOutput(LCD_GPIO_DATA_BASE, DATA_PINS);
	GPIOPinTypeGPIOOutput(LCD_GPIO_CTL_BASE, E_PIN | RS_PIN);

	// Check if use 8-bit data or 4-bit data
	data8Bit = (ui8FunctionSetOptions & FUNCTION_SET_8_BIT) > 0;

	delayMs(20);

	// Some mysterious magic
	lcdWriteCommand(0x30);
	delayMs(20);
	lcdWriteCommand(0x30);
	delayMs(20);
	lcdWriteCommand(0x30);
	delayMs(20);

	if (!data8Bit) {
		lcdWriteCommand(0x20);
		delayMs(20);
	}

	// initial setup
	lcdWriteCommand(FUNCTION_SET_BASE | ui8FunctionSetOptions);
	lcdWriteCommand(ENTRY_MODE_SET_BASE | ui8EntryModeSetOptions);
	lcdWriteCommand(DISPLAY_BASE | ui8DisplayOptions);
	lcdWriteCommand(CLEAR_DISPLAY);
}

