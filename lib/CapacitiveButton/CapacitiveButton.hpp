// File Name:           CapacitiveButton.cpp
// File Description:    Capacitive button class implementation

// Project Title:       Vetrina Entrata SAMB - CanSat 2021
// Project Category:    SAMB
// Project Code:        TR401
// Project Repository:  https://github.com/Tobia-Rossi/SAMB_TR401

// Author:              Tobia Rossi
// Author e-mail:       github@tobiarossi.ch

// Company Name:        SAMB
// Company Address:     Viale Stefano Franscini 25, 6502 Bellinzona, TI, CH
// Company e-mail:      decs-cpt.bellinzonaedu.ti.ch



#ifndef __CAPACITIVEBUTTON_HPP__
#define __CAPACITIVEBUTTON_HPP__



// Application Include
#include <Arduino.h>



// System Include
#include <stdint.h>



// Class Declaration
class CapacitiveButton
{
	public:
		// Methods
		CapacitiveButton() = delete;
		CapacitiveButton(uint32_t buttonPin, bool buttonPressedLevel);
		virtual ~CapacitiveButton();

		bool getButtonState() const;
		void setButtonPressedLevel(bool buttonPressedLevel);

		void setClickedInterruptFunction(void (*buttonCallBack) ());

		// Attributes
		// Not Allowed

	private:
		// Methods

		// Attributes
		uint32_t _buttonPin;
		bool _buttonPressedLevel;
};

#endif // __CAPACITIVEBUTTON_HPP__