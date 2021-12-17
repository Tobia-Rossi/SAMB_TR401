// File Name:           DemoBoard.hpp
// File Description:    Complete Board Class declarations

// Project Title:       Vetrina Entrata SAMB - CanSat 2021
// Project Category:    SAMB
// Project Code:        TR401
// Project Repository:  https://github.com/Tobia-Rossi/SAMB_TR401

// Author:              Tobia Rossi
// Author e-mail:       github@tobiarossi.ch

// Company Name:        SAMB
// Company Address:     Viale Stefano Franscini 25, 6502 Bellinzona, TI, CH
// Company e-mail:      decs-cpt.bellinzonaedu.ti.ch



#ifndef __DEMOBOARD_HPP__
#define __DEMOBOARD_HPP__

#include "Bluetooth.hpp"
#include "Buzzer.hpp"
#include "CapacitiveButton.hpp"
#include "Dht11.hpp"
#include "LedsBar.hpp"
#include "RgbLeds.hpp"
#include "SevenSegDisplays.hpp"
#include "Switch.hpp"

class DemoBoard
{
	public:
		DemoBoard();
		virtual~DemoBoard();

		// attribute classes
		Buzzer *buzzer;
		CapacitiveButton *capacitiveButton;
		LedsBar *ledsBar;
		Switch *switchCOrF;

	private:
	
};

#endif // __DEMOBOARD_HPP__