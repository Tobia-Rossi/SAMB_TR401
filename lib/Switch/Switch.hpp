// File Name:           Switch.cpp
// File Description:    Switch class implementation

// Project Title:       Vetrina Entrata SAMB - CanSat 2021
// Project Category:    SAMB
// Project Code:        TR401
// Project Repository:  https://github.com/Tobia-Rossi/SAMB_TR401

// Author:              Tobia Rossi
// Author e-mail:       github@tobiarossi.ch

// Company Name:        SAMB
// Company Address:     Viale Stefano Franscini 25, 6502 Bellinzona, TI, CH
// Company e-mail:      decs-cpt.bellinzonaedu.ti.ch



#ifndef __SWITCH_HPP__
#define __SWITCH_HPP__



// Application Include
#include <Arduino.h>



// System Include
#include <stdint.h>



// Class Declaration
class Switch
{
	public:
		// Methods
		Switch() = delete;
		Switch(uint32_t switchPin);
		virtual ~Switch();

		bool getSwitchState() const;

		void setChangedInterruptFunction(void (*switchCallBack) ());

		// Attributes
		// Not Allowed

	private:
		// Methods

		// Attributes
		uint32_t _switchPin;
};

#endif // __SWITCH_HPP__