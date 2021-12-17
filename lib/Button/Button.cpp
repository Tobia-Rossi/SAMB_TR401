// File Name:           Button.hpp
// File Description:    Button class declarations

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
#include "Button.hpp"



// System Includes



// Class Implementation

// Pubblic
Button::Button(uint32_t buttonPin, bool buttonPressedLevel)
{
	_buttonPin = buttonPin;
	_buttonPressedLevel = buttonPressedLevel;

	pinMode(_buttonPin, INPUT);
}

Button::~Button()
{

}

bool Button::getButtonState() const
{
	if (digitalRead(_buttonPin) == _buttonPressedLevel) {
		return true;
	} else {
		return false;
	}
}

void Button::setButtonPressedLevel(bool buttonPressedLevel)
{
	_buttonPressedLevel = buttonPressedLevel;
}

void Button::setClickedInterruptFunction(void (*buttonCallBack)())
{
	attachInterrupt(digitalPinToInterrupt(_buttonPin), buttonCallBack, RISING);
}

// Private