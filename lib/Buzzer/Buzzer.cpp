// File Name:           Buzzer.cpp
// File Description:    Buzzer class implementations

// Project Title:       Vetrina Entrata SAMB - CanSat 2021
// Project Category:    SAMB
// Project Code:        TR401
// Project Repository:  https://github.com/Tobia-Rossi/SAMB_TR401

// Author:              Tobia Rossi
// Author e-mail:       github@tobiarossi.ch

// Company Name:        SAMB
// Company Address:     Viale Stefano Franscini 25, 6502 Bellinzona, TI, CH
// Company e-mail:      decs-cpt.bellinzonaedu.ti.ch


// Application Includes
#include "Buzzer.hpp"



// System Includes



// Class Implementation
// Pubblic
Buzzer::Buzzer(uint32_t buzzerPin)
{
	_buzzerPin = buzzerPin;
	_buzzerSoundFrequency = 1000;
	_buzzerSoundDuration = 200;

	pinMode(_buzzerPin, OUTPUT);
}

Buzzer::Buzzer(uint32_t buzzerPin, uint32_t buzzerSoundFrequency, uint32_t buzzerSoundDuration)
{
	_buzzerPin = buzzerPin;
	_buzzerSoundFrequency = buzzerSoundFrequency;
	_buzzerSoundDuration = buzzerSoundDuration;

	pinMode(_buzzerPin, OUTPUT);
}

Buzzer::~Buzzer()
{
	
}

void Buzzer::setBuzzerSoundFrequency(uint32_t buzzerSoundFrequency)
{
	_buzzerSoundFrequency = buzzerSoundFrequency;
}

void Buzzer::setBuzzerSoundDuration(uint32_t buzzerSoundDuration)
{
	_buzzerSoundDuration = buzzerSoundDuration;
}

void Buzzer::makeSound(uint32_t soundFrequency, uint32_t soundDuration)
{
	tone(_buzzerPin, soundFrequency, soundDuration);
}

void Buzzer::makeSound()
{
	tone(_buzzerPin, _buzzerSoundFrequency, _buzzerSoundDuration);
}

// Private