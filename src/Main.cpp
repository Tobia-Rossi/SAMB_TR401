// File Name:           Main.cpp
// File Description:    Main file

// Project Title:       Vetrina Entrata SAMB - CanSat 2021
// Project Category:    SAMB
// Project Code:        TR401
// Project Repository:  https://github.com/Tobia-Rossi/SAMB_TR401

// Author:              Tobia Rossi
// Author e-mail:       github@tobiarossi.ch

// Company Name:        SAMB
// Company Address:     Viale Stefano Franscini 25, 6502 Bellinzona, TI, CH
// Company e-mail:      decs-cpt.bellinzona@edu.ti.ch



#include <Arduino.h>
#include "DemoBoard.hpp"

// Creates Demo Board Class Instance
static DemoBoard *demoBoard = new DemoBoard();

// Declaration of CallBack functions
void capacitiveButtonPressed();
void switchCOrFChanged();

void setup()
{
	for (int i = 0; i < 10; i++){
		if (demoBoard->ledsBar->getLedState((i - 1)) == false) {
			demoBoard->ledsBar->setLedState(i, true);
		} else {
			demoBoard->ledsBar->setLedState(i, false);
		}
	}

	demoBoard->capacitiveButton->setClickedInterruptFunction(capacitiveButtonPressed);
	demoBoard->switchCOrF->setChangedInterruptFunction(switchCOrFChanged);
}

void loop()
{

}

// Callbacks
void capacitiveButtonPressed()
{
	demoBoard->ledsBar->toggleBarState();
	demoBoard->buzzer->makeSound(2500, 300);
}

void switchCOrFChanged()
{
	demoBoard->ledsBar->toggleBarState();
}