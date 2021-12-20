// File Name:           BcdSevenSegDisplay.hpp
// File Description:    BCD Seven segment display class declarations

// Project Title:       Vetrina Entrata SAMB - CanSat 2021
// Project Category:    SAMB
// Project Code:        TR401
// Project Repository:  https://github.com/Tobia-Rossi/SAMB_TR401

// Author:              Tobia Rossi
// Author e-mail:       github@tobiarossi.ch

// Company Name:        SAMB
// Company Address:     Viale Stefano Franscini 25, 6502 Bellinzona, TI, CH
// Company e-mail:      decs-cpt.bellinzonaedu.ti.ch



#ifndef __BCDSEVENSEGDISPLAY_HPP__
#define __BCDSEVENSEGDISPLAY_HPP__



// Application Include
#include <Arduino.h>



// System Include
#include <stdint.h>



// Class Declaration
class BcdSevenSegDisplay
{
	public:
		// Methods
		BcdSevenSegDisplay() = delete;
		BcdSevenSegDisplay(uint32_t bcdSevenSegPins[4], bool bcdSevenSegActiveLevel = HIGH);
		virtual ~BcdSevenSegDisplay();

		void bcdSevenSegDisplaySetNumber(uint8_t number);
		void bcdSevenSegDisplaySetActiveLevel(bool bcdSevenSegActiveLevel);

		// Attributes
		// Not Allowed

	private:
		// Methods
		
		// Attributes
		uint32_t _bcdSevenSegPins[4];
		bool _bcdSevenSegActiveLevel;
};

#endif // __BCDSEVENSEGDISPLAY_HPP__