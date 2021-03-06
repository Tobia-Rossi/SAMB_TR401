// File Name:           Main.cpp
// File Description:    Main file

// Project Title:       Vetrina Entrata SAMB - CanSat 2021
// Project Category:    SAMB
// Project Code:        TR401
// Project Repository:  https://github.com/Tobia-Rossi/SAMB_TR401

// Author:              Tobia Rossi
// Author e-mail:       github@tobiarossi.ch

// Company Name:        SAMB
// Company Address:     Viale Stefano Franscini 25, 6502 Bellinzona, TI, CH
// Company e-mail:      decs-cpt.bellinzona@edu.ti.ch



// Application Includes
#include "DemoBoard.hpp"



// System Includes
#include <Arduino.h>



// Features
// #define FEAT_SERIAL_DEBUG



// Typedef
typedef enum { // When you modify add command to both switch cases below
	COMMAND_SET_LEDS_COLOR = 0x4C,
	COMMAND_CYCLE_COLORS = 0x5C,
	COMMAND_TOGGLE_CRAZY_MODE = 0x6C
} bleCommands;


// Constants
const uint32_t IntervalBtwReadings = 2000;
const uint32_t NumberOfColors = 9;

// BLT
const char ComunicationStartCode = 0x1C;
const char ComunicationIsCommandCode = 0x2C;
const char ComunicationIsTextCode = 0x3C;
const char CommandErrorCode = 0xFC;
const uint32_t TimeOutRecievingCommandData = 10000; // in milliseconds



// Static Variables
// Creates Demo Board Class Instance
static DemoBoard *demoBoard = new DemoBoard();
volatile static uint32_t colorListIndex = 0;

// Declaration of CallBack functions
void capacitiveButtonPressed();

// Pubblic Functions
void readDht11Sensor()
{
	// Temperature
	if (demoBoard->getTemperatureIsInCelsius() == true) {
		demoBoard->setSevenSegmentDisplaysNumber(demoBoard->dht11->readTemperature());
	} else {
		demoBoard->setSevenSegmentDisplaysNumber(demoBoard->dht11->readTemperature(true));
	}

	// Humidity
	demoBoard->ledsBar->setBarLevel(demoBoard->dht11->readHumidity());
}

void refreshRgbLeds()
{
	// ATTENTION SYNC WITH NUMBER OF LEDS
	switch (colorListIndex)
	{
	// SAMB Orange
	case 0:
		demoBoard->rgbLeds->setRgbColor(255, 40, 0);
		break;
	
	// Purple
	case 1:
		demoBoard->rgbLeds->setRgbColor(255, 98, 157);
		break;

	case 2:
		demoBoard->rgbLeds->setRgbColor(255, 0, 0);
		break;

	case 3:
		demoBoard->rgbLeds->setRgbColor(0, 255, 0);
		break;

	case 4:
		demoBoard->rgbLeds->setRgbColor(0, 0, 255);
		break;

	case 5:
		demoBoard->rgbLeds->setRgbColor(255, 255, 0);
		break;

	case 6:
		demoBoard->rgbLeds->setRgbColor(255, 0, 255);
		break;

	case 7:
		demoBoard->rgbLeds->setRgbColor(0, 255, 255);
		break;

	case 8:
		demoBoard->rgbLeds->setRgbColor(255, 255, 255);
		break;

	default:
		// OFF
		demoBoard->rgbLeds->setRgbColor(0, 0, 0);
		break;
	}

	demoBoard->setColorChanged(false);
}

void setup()
{
	for (int i = 0; i < 10; i++){
		demoBoard->ledsBar->setLedState(i, false);
	}

	demoBoard->setSevenSegmentDisplaysNumber(88);

	demoBoard->capacitiveButton->setClickedInterruptFunction(capacitiveButtonPressed);

	demoBoard->dht11->begin();

	refreshRgbLeds();
}

void loop()
{
	static uint8_t commandDataBytesToWait = 0;
	static char communicationMode = 0x00;
	static char commandToExecute = 0x00;

	static bool crazyMode = false;

	static uint32_t previousReadingsMillis = millis();
	static uint32_t startRecievingCommandData = millis();

	static char dummy = 0;

	// Reading interval elapsed actions
	if (millis() - previousReadingsMillis >= IntervalBtwReadings) {
		// Unit Check
		if (demoBoard->switchCOrF->getSwitchState() == false) {
			demoBoard->setTemperatureIsInCelsius(false);
		} else {
			demoBoard->setTemperatureIsInCelsius(true);
		}

		// Reading
		readDht11Sensor();
		previousReadingsMillis = millis();
	}

	// Refreshing RGB leds if button was pressed
	if (demoBoard->getColorChanged() == true) {
		refreshRgbLeds();
	}

// Bluetooth Comunication Recieve START
	// Capture comunication meaning
	if (demoBoard->getNumberOfBytesInBluetoothBuffer() >= 3 && (commandDataBytesToWait == 0)) {
		if (demoBoard->readByteFromBluetoothBuffer() == ComunicationStartCode) {
			communicationMode = demoBoard->readByteFromBluetoothBuffer();
			if (communicationMode == ComunicationIsCommandCode) {
				commandToExecute = demoBoard->readByteFromBluetoothBuffer();

				#ifdef FEAT_SERIAL_DEBUG
				Serial.print("Command Recieved:");
				Serial.println(commandToExecute, HEX);
				#endif // FEAT_SERIAL_DEBUG

				// Set how much data to wait for
				switch (commandToExecute) {
					case COMMAND_SET_LEDS_COLOR:
						commandDataBytesToWait = 3;
						break;

					case COMMAND_CYCLE_COLORS:
						commandDataBytesToWait = 0;
						break;

					case COMMAND_TOGGLE_CRAZY_MODE:
						commandDataBytesToWait = 0;
						break;
					
					default:
						#ifdef FEAT_SERIAL_DEBUG
						Serial.println("INVALID COMMAND");
						#endif // FEAT_SERIAL_DEBUG

						demoBoard->sendByteViaBluetooth('N');
						demoBoard->sendByteViaBluetooth('O');
						demoBoard->sendByteViaBluetooth('\n');
						commandToExecute = 0x00;
						commandDataBytesToWait = 0;
						break;
				}

				#ifdef FEAT_SERIAL_DEBUG
				Serial.print("Command to Execute: ");
				Serial.println(commandToExecute, HEX);
				Serial.print("Data to wait: ");
				Serial.println(commandDataBytesToWait);
				#endif // FEAT_SERIAL_DEBUG

				startRecievingCommandData = millis();
			} else if (communicationMode == ComunicationIsTextCode) {
				#ifdef FEAT_SERIAL_DEBUG
				Serial.print(demoBoard->readByteFromBluetoothBuffer());
				#endif // FEAT_SERIAL_DEBUG
			}
		}
	}

	// Execute commands if data has been recieved
	if ((commandDataBytesToWait <= demoBoard->getNumberOfBytesInBluetoothBuffer()) && (commandToExecute != 0x00)) {
		#ifdef FEAT_SERIAL_DEBUG
		Serial.print("Data Bytes Recieved: ");
		Serial.println(demoBoard->getNumberOfBytesInBluetoothBuffer(), DEC);
		Serial.print("Command in execution: ");
		Serial.println(commandToExecute, HEX);
		#endif // FEAT_SERIAL_DEBUG

		switch (commandToExecute) {
			case COMMAND_SET_LEDS_COLOR:
				#ifdef FEAT_SERIAL_DEBUG
				Serial.println("I'm here in 4C LOL");
				// Serial.print("R: ");
				// Serial.print(demoBoard->readByteFromBluetoothBuffer(), HEX);
				// Serial.print(" G: ");
				// Serial.print(demoBoard->readByteFromBluetoothBuffer(), HEX);
				// Serial.print(" B: ");
				// Serial.println(demoBoard->readByteFromBluetoothBuffer(), HEX);
				#endif // FEAT_SERIAL_DEBUG

				demoBoard->rgbLeds->setRgbColor(demoBoard->readByteFromBluetoothBuffer(), demoBoard->readByteFromBluetoothBuffer(), demoBoard->readByteFromBluetoothBuffer());
				break;

			case COMMAND_CYCLE_COLORS:
				// Makes Sound
				demoBoard->buzzer->makeSound(2700, 300);
		
				// Change Color
				demoBoard->setColorChanged(true);
		
				if (colorListIndex < (NumberOfColors - 1)) {
					colorListIndex++;
				} else {
					colorListIndex = 0;
				}
				break;

			case COMMAND_TOGGLE_CRAZY_MODE:
				crazyMode = !crazyMode;
				break;
			
			default:
				// Send Error code to Bluetooth
				demoBoard->sendByteViaBluetooth(CommandErrorCode);

				#ifdef FEAT_SERIAL_DEBUG
				Serial.println("COMMAND ERROR");
				#endif // FEAT_SERIAL_DEBUG
				break;
		}

		commandToExecute = 0x00;
		commandDataBytesToWait = 0;
	}

	// Timeout recieving data if it takes too long
	if ((commandToExecute != 0x00) && (millis() - startRecievingCommandData) >= TimeOutRecievingCommandData) {
		demoBoard->sendByteViaBluetooth('T');
		demoBoard->sendByteViaBluetooth('I');
		demoBoard->sendByteViaBluetooth('M');
		demoBoard->sendByteViaBluetooth('E');
		demoBoard->sendByteViaBluetooth('D');
		demoBoard->sendByteViaBluetooth(' ');
		demoBoard->sendByteViaBluetooth('O');
		demoBoard->sendByteViaBluetooth('U');
		demoBoard->sendByteViaBluetooth('T');
		demoBoard->sendByteViaBluetooth('\n');

		#ifdef FEAT_SERIAL_DEBUG
		Serial.println("Command has Timed Out");
		#endif // FEAT_SERIAL_DEBUG

		commandToExecute = 0;
		commandDataBytesToWait = 0;

		while (demoBoard->getNumberOfBytesInBluetoothBuffer() > 0) {
			(void) dummy;
			dummy = demoBoard->readByteFromBluetoothBuffer();
		}
	}
// Bluetooth Command Recieve END

// Bluetooth AT Command From PC START
	/*
	if (demoBoard->getNumberOfBytesInBluetoothBuffer() > 0) {
		Serial.print(demoBoard->readByteFromBluetoothBuffer());
	}

	if (Serial.available() > 0) {
		demoBoard->sendByteViaBluetooth(Serial.read());
	}
	*/
// Bluetooth AT Command From PC END

// Crazy Mode Start
	if (crazyMode) {
		if (colorListIndex < (NumberOfColors - 1)) {
			colorListIndex++;
			refreshRgbLeds();
		} else {
			colorListIndex = 0;
			refreshRgbLeds();
		}
		delay(50);
	}
// Crazy Mode End
}

// Callbacks
void capacitiveButtonPressed()
{
	// Makes Sound
	demoBoard->buzzer->makeSound(2700, 300);
	
	// Change Color
	demoBoard->setColorChanged(true);
	
	if (colorListIndex < (NumberOfColors - 1)) {
		colorListIndex++;
	} else {
		colorListIndex = 0;
	}
}