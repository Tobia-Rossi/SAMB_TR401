// File Name:           RgbLed.cpp
// File Description:    Rgb Leds Module class Implementations

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
#include "RgbLed.hpp"



// System Inlcudes



// Class Implementation

// Public
RgbLed::RgbLed(uint32_t redLedPin, uint32_t greenLedPin, uint32_t blueLedPin, uint8_t bitPwmResolution, bool ledsOnLevel)
{
	_ledPins = new uint32_t[3];
	_ledPins[0] = redLedPin;
	_ledPins[1] = greenLedPin;
	_ledPins[2] = blueLedPin;

	_ledsOnLevel = ledsOnLevel;

	_ledsColors = new uint16_t[3];
	_ledsColors[0] = 0;
	_ledsColors[1] = 0;
	_ledsColors[2] = 0;

	_maxColorValue = pow(2, bitPwmResolution) - 1;

	pinMode(_ledPins[0], OUTPUT);
	pinMode(_ledPins[1], OUTPUT);
	pinMode(_ledPins[2], OUTPUT);

	analogWriteResolution(bitPwmResolution);

	digitalWrite(_ledPins[0], !_ledsOnLevel);
	digitalWrite(_ledPins[1], !_ledsOnLevel);
	digitalWrite(_ledPins[2], !_ledsOnLevel);
}

RgbLed::~RgbLed()
{
	delete _ledPins;
	_ledPins = nullptr;

	delete _ledsColors;
	_ledsColors = nullptr;
}

void RgbLed::setRedLed(uint16_t redValue)
{
	_ledsColors[0] = redValue;
	refreshLedColor();
}

void RgbLed::setGreenLed(uint16_t greenValue)
{
	_ledsColors[1] = greenValue;
	refreshLedColor();
}

void RgbLed::setBlueLed(uint16_t blueValue)
{
	_ledsColors[2] = blueValue;
	refreshLedColor();
}

void RgbLed::setRgbColor(uint16_t redValue, uint16_t greenValue, uint16_t blueValue)
{
	_ledsColors[0] = redValue;
	_ledsColors[1] = greenValue;
	_ledsColors[2] = blueValue;
	refreshLedColor();
}

uint16_t RgbLed::getRedColor() const
{
	return _ledsColors[0];
}

uint16_t RgbLed::getGreenColor() const
{
	return _ledsColors[1];
}

uint16_t RgbLed::getBlueColor() const
{
	return _ledsColors[2];
}



// Private

void RgbLed::refreshLedColor()
{
	if(_ledsOnLevel) {
		analogWrite(_ledPins[0], _ledsColors[0]);
		analogWrite(_ledPins[1], _ledsColors[1]);
		analogWrite(_ledPins[2], _ledsColors[2]);
	} else {
		analogWrite(_ledPins[0], _maxColorValue - _ledsColors[0]);
		analogWrite(_ledPins[1], _maxColorValue - _ledsColors[1]);
		analogWrite(_ledPins[2], _maxColorValue - _ledsColors[2]);
	}
}