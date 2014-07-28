/*
 * lcd.h - Prototypes for controlling a standard 16x2 lcd
 *
 *  Created on: Jul 7, 2014
 *      Author: Cuong T. Nguyen
 */

#ifndef LCD_H_
#define LCD_H_

/*
 * Pins interfacing:
 * RS   --- PA2
 * R/W  --- GND
 * E    --- PA3
 * DB0  --- Not used
 * DB1  --- Not used
 * DB2  --- Not used
 * DB3  --- Not used
 * DB4  --- PA4
 * DB5  --- PA5
 * DB6  --- PA6
 * DB7  --- PA7
 */

/*
 * Command codes. Some commands require the BASE constant
 */
#define FUNCTION_SET_BASE 			0x20
#define FUNCTION_SET_8_BIT 			0x10 // 4-bit display by default
#define FUNCTION_SET_2_LINES 		0x08 // 1 line by default
#define FUNCTION_SET_5_10_DOTS 		0x04 // 5x7 dots by default
#define ENTRY_MODE_SET_BASE 		0x04
#define ENTRY_MODE_SET_INCREMENT 	0x02 // Decrement cursor position by default
#define ENTRY_MODE_SET_SHIFT 		0x01 // No display shift by default
#define DISPLAY_BASE 				0x08
#define DISPLAY_ON 					0x04
#define DISPLAY_CURSOR 				0x02
#define DISPLAY_CURSOR_BLINK 		0x01

#define SHIFT_BASE 					0x10
#define SHIFT_DISPLAY 				0x08 // cursor move by default
#define SHIFT_RIGHT 				0x04 // shift to the left by default
#define CLEAR_DISPLAY 0x01
#define RETURN_HOME 0x02

/*
 * Change this according to pins interfacing
 */
#define LCD_GPIO_DATA_PERIPH 		SYSCTL_PERIPH_GPIOA
#define LCD_GPIO_CTL_PERIPH 		SYSCTL_PERIPH_GPIOA
#define LCD_GPIO_DATA_BASE 			GPIO_PORTA_BASE // port for sending data
#define LCD_GPIO_CTL_BASE 			GPIO_PORTA_BASE  // port for controlling RS, RW and E
#define DATA_PINS 					(GPIO_PIN_4| GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7)
#define RS_PIN 						GPIO_PIN_2
//#define RW_PIN 						GPIO_PIN_1
#define E_PIN 						GPIO_PIN_3

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

void lcdInit(uint8_t functionSetOptions, uint8_t entryModeSetOptions,
		uint8_t displayOptions);

/*
 * Write data to Data pins. Written data might be 4-bit or 8-bit
 * according to data8Bit variable
 */
void lcdWriteData(uint8_t data);

/*
 * Send command to the LCD
 */
void lcdWriteCommand(uint8_t com);

/*
 * Write a char to the LCD at the current string
 */
void lcdWriteChar(char ch);

/*
 * Write a string to the LCD
 */
void lcdWriteString(char * s);

/*
 * Clear the display then write the string
 */
void lcdClearAndWriteString(char * s);

/*
 * Set cursor at the specified coordinate in which x is the column and y is the row
 */
void lcdGoToXY(uint8_t x, uint8_t y);

/*
 * Clear Display
 */
void lcdClear();

#endif /* LCD_H_ */
