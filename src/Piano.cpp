// Piano.cpp

#include "Piano.h"

extern Sound sound;

// Piano class functions:
// public:
void Piano::playNoteC(void) {
	uint8_t cIdx = cPosition + sound.octave * majorNotesSize;
	sound.start(toneTab[cIdx]);
	Delay();
	sound.stop();
}

void Piano::playNoteD(void) {
	uint8_t dIdx = dPosition + sound.octave * majorNotesSize;
	sound.start(toneTab[dIdx]);
	Delay();
	sound.stop();
}

void Piano::playNoteE(void) {
	uint8_t eIdx = ePosition + sound.octave * majorNotesSize;
	sound.start(toneTab[eIdx]);
	Delay();
	sound.stop();
}

void Piano::playNoteF(void) {
	uint8_t fIdx = fPosition + sound.octave * majorNotesSize;
	sound.start(toneTab[fIdx]);
	Delay();
	sound.stop();
}

void Piano::playNoteG(void) {
	uint8_t gIdx = gPosition + sound.octave * majorNotesSize;
	sound.start(toneTab[gIdx]);
	Delay();
	sound.stop();
}

void Piano::playNoteA(void) {
	uint8_t aIdx = aPosition + sound.octave * majorNotesSize;
	sound.start(toneTab[aIdx]);
	Delay();
	sound.stop();
}

void Piano::playNoteB(void) {
	uint8_t bIdx = bPosition + sound.octave * majorNotesSize;
	sound.start(toneTab[bIdx]);
	Delay();
	sound.stop();
}
