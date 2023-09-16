#ifndef MUSIC_H
#define MUSIC_H

// #pragma once

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "SysTick.h"

struct Note {
	const uint8_t toneIdx, delay;
};
typedef const struct Note note;

class Music {
private:
	const uint32_t toneTab[21] = {
		30534,27211,24242,22923,20408,18182,16194, // C4 major notes
		15289,13621,12135,11454,10204,9091,8099, // C5 major notes
		7645,6810,6067,5727,5102,4545,4050	// C6 major notes	
	};
	static const uint8_t songsSize = 3;
	const note* songs[songsSize];
	uint8_t songIdx;
	bool play;
	void GPIOPortA_Init();
	void Delay();

public:
	Music(void);
	void nextSong(void);
	bool isOn(void);
	void turnOff(void);
	void turnOn(void);
	void playSongNotes(void);
};

#endif
