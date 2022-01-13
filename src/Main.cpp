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



// Constants
const uint32_t IntervalBtwReadings = 2000;
const uint32_t NumberOfColors = 8;



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

	default:
		// OFF
		demoBoard->rgbLeds->setRgbColor(0, 0, 0);
		break;
	}
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
	static uint32_t previousReadingsMillis = millis();

	// Reading interval elapsed actions
	if (millis() - previousReadingsMillis >= IntervalBtwReadings) {
		// Unit Check
		if (demoBoard->switchCOrF->getSwitchState() == true) {
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

// Crazy Mode Start
	/*
	if (colorListIndex < (NumberOfColors - 1)) {
		colorListIndex++;
		refreshRgbLeds();
	} else {
		colorListIndex = 0;
		refreshRgbLeds();
	}
	delay(50);
	*/
// Crazy Mode End
}

// Callbacks
void capacitiveButtonPressed()
{
	// Makes Sound
	demoBoard->buzzer->makeSound(2500, 300);
	
	// Change Color
	demoBoard->setColorChanged(true);
	
	if (colorListIndex < (NumberOfColors - 1)) {
		colorListIndex++;
	} else {
		colorListIndex = 0;
	}
}