// File Name:           BcdSevenSegDisplay.cpp
// File Description:    BCD Seven segment display class implementations

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
#include "BcdSevenSegDisplay.hpp"



// System Includes



// Class Implementation

// Public

BcdSevenSegDisplay::BcdSevenSegDisplay(uint32_t bcdSevenSegPins[4], bool bcdSevenSegActiveLevel)
{
	_bcdSevenSegPins[0] = bcdSevenSegPins[0];
	_bcdSevenSegPins[1] = bcdSevenSegPins[1];
	_bcdSevenSegPins[2] = bcdSevenSegPins[2];
	_bcdSevenSegPins[3] = bcdSevenSegPins[3];

	pinMode(_bcdSevenSegPins[0], OUTPUT);
	pinMode(_bcdSevenSegPins[1], OUTPUT);
	pinMode(_bcdSevenSegPins[2], OUTPUT);
	pinMode(_bcdSevenSegPins[3], OUTPUT);

	_bcdSevenSegActiveLevel = bcdSevenSegActiveLevel;
}

BcdSevenSegDisplay::~BcdSevenSegDisplay()
{

}


void BcdSevenSegDisplay::bcdSevenSegDisplaySetNumber(uint8_t number)
{
	for (int i = 0; i < 4; i++) {
		if ((number & (0x01 << i)) == (0x01 << i)) {
			digitalWrite(_bcdSevenSegPins[i], _bcdSevenSegActiveLevel);
		} else {
			digitalWrite(_bcdSevenSegPins[i], !_bcdSevenSegActiveLevel);
		}
	}
}

void BcdSevenSegDisplay::bcdSevenSegDisplaySetActiveLevel(bool bcdSevenSegActiveLevel)
{
	_bcdSevenSegActiveLevel = bcdSevenSegActiveLevel;
}

// Private