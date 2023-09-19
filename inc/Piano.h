#ifndef PIANO_H
#define PIANO_H

#include <stdint.h>
#include "Sound.h"

class Piano : public Sound {
private:
	enum notePosition {
		cPosition, dPosition, ePosition, fPosition, gPosition, aPosition, bPosition
	};

public:
	void playNoteC(void);
	void playNoteD(void);
	void playNoteE(void);
	void playNoteF(void);
	void playNoteG(void);
	void playNoteA(void);
	void playNoteB(void);
	void turnOn(void);
};

#endif
