// File Name:           Switch.hpp
// File Description:    Switch class declarations

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
#include "Switch.hpp"



// System Includes



// Class Implementation

// Pubblic
Switch::Switch(uint32_t switchPin)
{
	_switchPin = switchPin;

	pinMode(_switchPin, INPUT);
}

Switch::~Switch()
{

}

bool Switch::getSwitchState() const
{
	if (digitalRead(_switchPin)) {
		return true;
	} else {
		return false;
	}
}

void Switch::setChangedInterruptFunction(void (*switchCallBack)())
{
	attachInterrupt(digitalPinToInterrupt(_switchPin), switchCallBack, CHANGE);
}

// Private