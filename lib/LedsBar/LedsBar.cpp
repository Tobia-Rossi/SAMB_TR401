// File Name:           LedsBar.cpp
// File Description:    Leds bar display class implementations

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
#include "LedsBar.hpp"



// System Includes



// Class Implementation

// Public
LedsBar::LedsBar()
{
	_numOfLeds = 1;
	_ledsPins = new uint32_t[_numOfLeds];
	_ledsOnLevel = HIGH;

	*_ledsPins = LED_BUILTIN;

	ledsInit();
}

LedsBar::LedsBar(uint32_t numOfLeds, uint32_t ledsPins[], bool ledOnLevel)
{
	_numOfLeds = numOfLeds;
	_ledsOnLevel = ledOnLevel;
	_ledsPins = new uint32_t[_numOfLeds];

	for (uint32_t i = 0; i < _numOfLeds; i++) {
		_ledsPins[i] = ledsPins[i];
	}

	ledsInit();
}

LedsBar::~LedsBar()
{
	delete _ledsPins;
	_ledsPins = nullptr;
}

void LedsBar::setLedState(uint32_t ledNum, bool state)
{
	if (ledNum < _numOfLeds) {
		if (state == true) {
			digitalWrite(_ledsPins[ledNum], _ledsOnLevel);
		} else {
			digitalWrite(_ledsPins[ledNum], !_ledsOnLevel);
		}
	}
}

bool LedsBar::getLedState(uint32_t ledNum)
{
	if (ledNum < _numOfLeds) {
		if (digitalRead(_ledsPins[ledNum]) == _ledsOnLevel) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

void LedsBar::setBarLevel(float percentual)
{
	_barLevel = percentual;

	for (uint32_t i = 0; i < _numOfLeds; i++) {
		if (i < (uint32_t)(percentual / (100.0 / _numOfLeds))) {
			setLedState(i, _ledsOnLevel);
		} else {
			setLedState(i, !_ledsOnLevel);
		}
	}
}

float LedsBar::getBarLevel()
{
	return _barLevel;
}

void LedsBar::toggleBarState()
{
	for (uint32_t i = 0; i < _numOfLeds; i++) {
		setLedState(i, !getLedState(i));
	}
}

// Private
void LedsBar::ledsInit()
{
	for (uint32_t i = 0; i < _numOfLeds; i++) {
		pinMode(_ledsPins[i], OUTPUT);
		setLedState(i, !_ledsOnLevel);
	}
}