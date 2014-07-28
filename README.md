#16x2 LCD driver API using TivaWare™ C Series

##Description

This is an API for Tiva™ C Series Launchpad from Texas Instrument to control a [16x2 LCD](http://www.8051projects.net/lcd-interfacing/index.php)

Supported commands: 

* Clear Display
* Return Home
* Entry Mode Set
* Display ON/OFF control
* Cursor & Display shift
* Function set

No support for adding and displaying custom characters yet.

##Usage

###Installation

* Add the TivaWare™ C Series library to your project.
* Add the **lcd.c** and **lcd.h** files to your project, then include **lcd.h** in your source code.
* Change the ports and pins definition in the **lcd.h** header file according to your hardware ports and pins interfacing.

###Functions

**I.** ``void lcdInit(FunctionSetOptions, EntryModeSetOptions, DisplayOptions)``

**Description **

Initialize the LCD with several options.

**Parameters**

*FunctionSetOptions*: Set data width, number of lines and character font.

*EntryModeSetOptions*: Set the cursor move direction and enables/disables the display.

*DisplayOptions*: Turn the display On/Off or the cursor On/Off and blink of the cursor.

**Example**

```
void main() {
	lcdInit(FUNCTION_SET_8_BIT | FUNCTION_SET_2_LINES, ENTRY_MODE_SET_INCREMENT, DISPLAY_ON);
    while (1) {
    ...
    }
}
```

* The options are separated with the OR operator ( | ).
* DISPLAY_ON should always be used to turn the display on at the start. 
* Look into the **lcd.h** file for more options.

**II.** ``void lcdWriteChar(char cChar)``

Write a charater to the LCD at the cursor's position.

**III.** ``void lcdWriteString(char *s) ``

Write a string to the LCD. If the string exceeds 16 characters, only first 16 characters will be kept. 

**Example**

```
void main() {
	lcdInit(...);
    while (1) {
    	lcdWriteString('Hello world!');
        // There should be a 20ms delay here
    }
}
```

**V.** ``void lcdWriteCommand(com)``

Send a command to the LCD. For more commands, refer [here](http://www.8051projects.net/lcd-interfacing/commands.php).

**Example**

```
void main() {
	lcdInit(...);
    while (1) {
        lcdWriteString('Helll world!');
    	lcdWriteCommand(0x02);  // Return the cursor to home
        lcdWriteString('Hello')
        // There should be a 20ms delay here
    }
    /* The result is: Hello world! */
}
```


**V.** ``void lcdClear()``

Clear the display

**VI.** ``void lcdClearAndWriteString(char *s)``

Clear the display then write the string 

**VII.** ``void lcdGoToXY(x, y)``

Set the cursor at the x column and y row (0-based). 


##Testing

Tested on Tiva™ C Series LaunchPad

##License

This project is released under the MIT License. 