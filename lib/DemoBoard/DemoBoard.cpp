// File Name:           DemoBoard.cpp
// File Description:    Complete Board Class implementations

// Project Title:       Vetrina Entrata SAMB - CanSat 2021
// Project Category:    SAMB
// Project Code:        TR401
// Project Repository:  https://github.com/Tobia-Rossi/SAMB_TR401

// Author:              Tobia Rossi
// Author e-mail:       github@tobiarossi.ch

// Company Name:        SAMB
// Company Address:     Viale Stefano Franscini 25, 6502 Bellinzona, TI, CH
// Company e-mail:      decs-cpt.bellinzonaedu.ti.ch


// Application Includes
#include "DemoBoard.hpp"

// Definitions
#define BLUETOOTH Serial1

// Static variables
static uint32_t umidityBarPins[10] = {23, 22, 21, 20, 19, 18, 17, 16, 15, 14};
static uint32_t sevenSegmentDisplayTensPins[4] = {41, 40, 39, 38};
static uint32_t sevenSegmentDisplayUnitsPins[4] = {37, 36, 35, 34};

// Class Implementations

// Public
DemoBoard::DemoBoard()
{
	_sevenSegmentDisplayTens = new BcdSevenSegDisplay(sevenSegmentDisplayTensPins);
	_sevenSegmentDisplayUnits = new BcdSevenSegDisplay(sevenSegmentDisplayUnitsPins);
	capacitiveButton = new Button(13, HIGH);
	buzzer = new Buzzer(2);
	dht11 = new DHT(33, DHT11);
	ledsBar = new LedsBar(10, umidityBarPins, HIGH);
	rgbLeds = new RgbLed(10, 11, 12, 8, HIGH);
	switchCOrF = new Switch(32);

	BLUETOOTH.begin(115200);

	_sevenSegmentDisplaysNumber = 88;
	_temperatureIsInCelsius = !switchCOrF->getSwitchState();
	_colorChanged = false;
}

DemoBoard::~DemoBoard()
{
	// Delete Capacitive Button
	delete capacitiveButton;
	capacitiveButton = nullptr;

	// Delete Buzzer
	delete buzzer;
	buzzer = nullptr;

	// Delete DHT11
	delete dht11;
	dht11 = nullptr;

	// Delete LedsBar
	delete ledsBar;
	ledsBar = nullptr;

	// Delete RGB Leds
	delete rgbLeds;
	rgbLeds = nullptr;

	// Delete Switch C or F
	delete switchCOrF;
	switchCOrF = nullptr;
}

void DemoBoard::setSevenSegmentDisplaysNumber(uint8_t number)
{
	_sevenSegmentDisplaysNumber = number;

	_sevenSegmentDisplayTens->bcdSevenSegDisplaySetNumber((_sevenSegmentDisplaysNumber / 10));
	_sevenSegmentDisplayUnits->bcdSevenSegDisplaySetNumber((_sevenSegmentDisplaysNumber % 10));}

uint8_t DemoBoard::getSevenSegmentDisplaysNumber() const
{
	return _sevenSegmentDisplaysNumber;
}

void DemoBoard::setTemperatureIsInCelsius(bool temperatureIsInCelsius)
{
	_temperatureIsInCelsius = temperatureIsInCelsius;
}

bool DemoBoard::getTemperatureIsInCelsius() const
{
	return _temperatureIsInCelsius;
}

void DemoBoard::setColorChanged(bool colorChanged)
{
	_colorChanged = colorChanged;
}

bool DemoBoard::getColorChanged() const
{
	return _colorChanged;
}

void DemoBoard::sendByteViaBluetooth(char byteToSend)
{
	BLUETOOTH.print(byteToSend);
}

char DemoBoard::getNumberOfBytesInBluetoothBuffer() const
{
	return BLUETOOTH.available();
}

char DemoBoard::readByteFromBluetoothBuffer() const 
{
	return BLUETOOTH.read();
}

// Private