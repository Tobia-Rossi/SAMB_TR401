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



// Definitions
#define READINGS_INTERVAL 2000



// Creates Demo Board Class Instance
static DemoBoard *demoBoard = new DemoBoard();

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

void setup()
{
	for (int i = 0; i < 10; i++){
		demoBoard->ledsBar->setLedState(i, false);
	}

	demoBoard->setSevenSegmentDisplaysNumber(88);

	demoBoard->capacitiveButton->setClickedInterruptFunction(capacitiveButtonPressed);

	demoBoard->dht11->begin();
}

void loop()
{
	static uint32_t previousReadingsMillis = millis();

	// Reading interval elapsed actions
	if (millis() - previousReadingsMillis >= READINGS_INTERVAL) {
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
}

// Callbacks
void capacitiveButtonPressed()
{
	// Makes Sound
	demoBoard->buzzer->makeSound(2500, 300);
	
	// TODO: ADD RGB LEDS COLOR LIST RANDOM SELECT TOGGLE
}