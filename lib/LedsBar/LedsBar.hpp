// File Name:           LedsBar.hpp
// File Description:    Leds bar display class declarations

// Project Title:       Vetrina Entrata SAMB - CanSat 2021
// Project Category:    SAMB
// Project Code:        TR401
// Project Repository:  https://github.com/Tobia-Rossi/SAMB_TR401

// Author:              Tobia Rossi
// Author e-mail:       github@tobiarossi.ch

// Company Name:        SAMB
// Company Address:     Viale Stefano Franscini 25, 6502 Bellinzona, TI, CH
// Company e-mail:      decs-cpt.bellinzona@edu.ti.ch




#ifndef __LEDSBAR_HPP__
#define __LEDSBAR_HPP__



// Application Include
#include <Arduino.h>



// System Include
#include <stdint.h>



// Class Declaration
class LedsBar
{
	public:
		// Methods
		LedsBar();
		LedsBar(uint32_t numOfLeds, uint32_t ledsPins[], bool ledOnLevel);
		virtual ~LedsBar();

		void setLedState(uint32_t ledNum, bool state);
		bool getLedState(uint32_t ledNum) const;

		void setBarLevel(float percentual);
		float getBarLevel() const;

		void toggleBarState();
		void setLedOnLevel(bool ledOnLevel);

		// Attributes
		// Not Allowed
		
	private:
		// Methods
		void ledsInit();

		// Attributes
		uint32_t _numOfLeds;
		uint32_t *_ledsPins;
		bool _ledsOnLevel;
		float _barLevel;
};

#endif // __LEDSBAR_HPP__