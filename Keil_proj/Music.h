#ifndef MUSIC_H
#define MUSIC_H

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Sound.h"

class Music : public Sound {
private:
	static const uint8_t songsSize = 3;
	const note* songs[songsSize];
	uint8_t songIdx;
	bool play;

public:
	Music(void);
	void nextSong(void);
	void playSong(void);
};

#endif
