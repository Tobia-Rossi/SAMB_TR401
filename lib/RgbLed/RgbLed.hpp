// File Name:           RgbLed.hpp
// File Description:    Rgb Leds Module class declarations

// Project Title:       Vetrina Entrata SAMB - CanSat 2021
// Project Category:    SAMB
// Project Code:        TR401
// Project Repository:  https://github.com/Tobia-Rossi/SAMB_TR401

// Author:              Tobia Rossi
// Author e-mail:       github@tobiarossi.ch

// Company Name:        SAMB
// Company Address:     Viale Stefano Franscini 25, 6502 Bellinzona, TI, CH
// Company e-mail:      decs-cpt.bellinzonaedu.ti.ch



#ifndef __RGBLED_HPP__
#define __RGBLED_HPP__



// Application Include
#include <Arduino.h>



// System Include
#include <stdint.h>



// Class Declaration
class RgbLed
{
	public:
		// Methods
		RgbLed() = delete;
		RgbLed(uint32_t redLedPin, uint32_t greenLedPin, uint32_t blueLedPin, uint8_t bitPwmResolution, bool ledsOnLevel = HIGH);
		virtual ~RgbLed();

		void setRedLed(uint16_t redValue);
		void setGreenLed(uint16_t greenValue);
		void setBlueLed(uint16_t blueValue);
		void setRgbColor(uint16_t redValue, uint16_t greenValue, uint16_t blueValue);

		uint16_t getRedColor() const;
		uint16_t getGreenColor() const;
		uint16_t getBlueColor() const;

		// Attributes
		// Not Allowed

	private:
		// Methods
		void refreshLedColor();

		// Attributes
		uint32_t *_ledPins;
		bool _ledsOnLevel;
		uint16_t *_ledsColors;
		uint16_t _maxColorValue;

};

#endif // __RGBLED_HPP__