// File Name:           Buzzer.hpp
// File Description:    Buzzer class declarations

// Project Title:       Vetrina Entrata SAMB - CanSat 2021
// Project Category:    SAMB
// Project Code:        TR401
// Project Repository:  https://github.com/Tobia-Rossi/SAMB_TR401

// Author:              Tobia Rossi
// Author e-mail:       github@tobiarossi.ch

// Company Name:        SAMB
// Company Address:     Viale Stefano Franscini 25, 6502 Bellinzona, TI, CH
// Company e-mail:      decs-cpt.bellinzonaedu.ti.ch



// Application Include
#include <Arduino.h>



// System Include
#include <stdint.h>



// Class Declaration
#ifndef __BUZZER_HPP__
#define __BUZZER_HPP__

class Buzzer
{
	public:
		// Methods
		Buzzer() = delete;
		Buzzer(uint32_t buzzerPin);
		Buzzer(uint32_t buzzerPin, uint32_t buzzerSoundFrequency, uint32_t buzzerSoundDuration);
		virtual ~Buzzer();

		void setBuzzerSoundFrequency(uint32_t buzzerSoundFrequency);
		void setBuzzerSoundDuration(uint32_t buzzerSoundDuration);

		void makeSound();
		void makeSound(uint32_t soundFrequency, uint32_t soundDuration);
		

		// Attributes
		// Not Allowed
		
	private:
		// Methods

		// Attributes
		uint32_t _buzzerPin;
		uint32_t _buzzerSoundFrequency;
		uint32_t _buzzerSoundDuration;
};

#endif // __BUZZER_HPP__