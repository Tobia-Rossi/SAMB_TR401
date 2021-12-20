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

#include "BcdSevenSegDisplay.hpp"
#include "Bluetooth.hpp"
#include "Button.hpp"
#include "Buzzer.hpp"
#include "DHT.h"
#include "LedsBar.hpp"
#include "RgbLeds.hpp"
#include "Switch.hpp"

class DemoBoard
{
	public:
		// Methods
		DemoBoard();
		virtual~DemoBoard();

		void setSevenSegmentDisplaysNumber(uint8_t number);
		uint8_t getSevenSegmentDisplaysNumber() const;

		void setTemperatureIsInCelsius(bool temperatureIsInCelsius);
		bool getTemperatureIsInCelsius();

		// Attribute classes
		Button *capacitiveButton;
		Buzzer *buzzer;
		DHT *dht11;
		LedsBar *ledsBar;
		Switch *switchCOrF;

	private:
		// Methods

		// Attributes
		BcdSevenSegDisplay *_sevenSegmentDisplayTens;
		BcdSevenSegDisplay *_sevenSegmentDisplayUnits;
		uint8_t _sevenSegmentDisplaysNumber;
		bool _temperatureIsInCelsius;
	
};

#endif // __DEMOBOARD_HPP__