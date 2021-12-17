// File Name:           DemoBoard.cpp
// File Description:    Complete Board Class implementations

// Project Title:       Vetrina Entrata SAMB - CanSat 2021
// Project Category:    SAMB
// Project Code:        TR401
// Project Repository:  https://github.com/Tobia-Rossi/SAMB_TR401

// Author:              Tobia Rossi
// Author e-mail:       github@tobiarossi.ch

// Company Name:        SAMB
// Company Address:     Viale Stefano Franscini 25, 6502 Bellinzona, TI, CH
// Company e-mail:      decs-cpt.bellinzonaedu.ti.ch



#include "DemoBoard.hpp"

// static variables
static uint32_t umidityBarPins[10] = {23, 22, 21, 20, 19, 18, 17, 16, 15, 14};

DemoBoard::DemoBoard()
{
	buzzer = new Buzzer(2);
	capacitiveButton = new Button(13, HIGH);
	ledsBar = new LedsBar(10, umidityBarPins, HIGH);
	switchCOrF = new Switch(32);
}

DemoBoard::~DemoBoard()
{
	// Delete Buzzer
	delete buzzer;
	buzzer = nullptr;

	// Delete Capacitive Button
	delete capacitiveButton;
	capacitiveButton = nullptr;

	// Delete LedsBar
	delete ledsBar;
	ledsBar = nullptr;

	// Delete Switch C or F
	delete switchCOrF;
	switchCOrF = nullptr;
}