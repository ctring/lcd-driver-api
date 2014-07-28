#Standard 16x2 LCD driver API using TivaWare™ C Series

##Description

This is an API for Tiva™ C Series Launchpad from Texas Instrument to control a [standard 16x2 LCD](http://www.8051projects.net/lcd-interfacing/index.php)

Supported commands: 

* Clear Display
* Return Home
* Entry Mode Set
* Display ON/OFF control
* Cursor & Display shift
* Function set

No support for adding and displaying custom characters yet.


##Usage

* First, add the TivaWare™ C Series library to your project.
* Add the **lcd.c** and **lcd.h** files to your project, then include **lcd.h** in your source code.
* Change the ports and pins definition in the **lcd.h** header file according to your hardware ports and pins interfacing.


##Testing

Tested on Tiva™ C Series LaunchPad

##License

This project is released under the MIT License. 