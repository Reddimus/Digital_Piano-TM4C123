#ifndef SOUND_H
#define SOUND_H

#define DAC (*((volatile unsigned long *)0x400051FC))
#define PIANO false
#define MUSIC true

#include <stdint.h>
#include "tm4c123gh6pm.h"

extern "C" {
	void SysTick_Handler(void);
}

class Sound {
private:
	void DAC_Init(void);

	static const uint8_t samplesSize = 64;
	const uint8_t ocativeSize = 3;
	volatile uint8_t sineWaveIdx;
	bool volatile mode;

	const uint8_t SineWave[samplesSize] = {
		32,35,38,41,44,47,49,52,54,56,58,59,61,62,62,63,63,63,62,62,
		61,59,58,56,54,52,49,47,44,41,38,35,32,29,26,23,20,17,15,12,
		10, 8, 6, 5, 3, 2, 2, 1, 1, 1, 2, 2, 3, 5, 6, 8,10,12,15,17,
		20,23,26,29
	};

public:
	void init(void);
	void updateDAC(void);
	void start(unsigned long period);
	void stop(void);
	void nextOctave(void);
	void Delay(void);
	void setMode(bool m);
	bool getMode(void);

	struct Note {
		const uint8_t toneIdx, delay;
	};
	typedef const struct Note note;

	const uint32_t toneTab[28] = {
		122137,108844,96970,91429,81633,72727,64777,
		30534*2,27211*2,24242*2,22923*2,20408*2,18182*2,16194*2,
		15289*2,13621*2,12135*2,11454*2,10204*2,9091*2,8099*2,
		7645*2,6810*2,6067*2,5727*2,5102*2,4545*2,4050*2
	};

	const uint8_t pause = 255, majorNotesSize = 7;
	uint8_t octave;
};

#endif
