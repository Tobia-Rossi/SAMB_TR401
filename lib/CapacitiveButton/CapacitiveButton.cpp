// File Name:           CapacitiveButton.hpp
// File Description:    Capacitive button class declarations

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
#include "CapacitiveButton.hpp"



// System Includes



// Class Implementation

// Pubblic
CapacitiveButton::CapacitiveButton(uint32_t buttonPin, bool buttonPressedLevel)
{
	_buttonPin = buttonPin;
	_buttonPressedLevel = buttonPressedLevel;

	pinMode(_buttonPin, INPUT);
}

CapacitiveButton::~CapacitiveButton()
{

}

bool CapacitiveButton::getButtonState() const
{
	if (digitalRead(_buttonPin) == _buttonPressedLevel) {
		return true;
	} else {
		return false;
	}
}

void CapacitiveButton::setButtonPressedLevel(bool buttonPressedLevel)
{
	_buttonPressedLevel = buttonPressedLevel;
}

void CapacitiveButton::setClickedInterruptFunction(void (*buttonCallBack)())
{
	attachInterrupt(digitalPinToInterrupt(_buttonPin), buttonCallBack, RISING);
}

// Private