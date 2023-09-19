// Music.cpp

#include "Music.h"

extern Sound sound;

class Song : public Sound {
private:
	enum noteNames { 
		C3, D3, E3, F3, G3, A3, B3,
		C4, D4, E4, F4, G4, A4, B4, 
		C5, D5, E5, F5, G5, A5, B5, 
		C6, D6, E6, F6, G6, A6, B6
	};
	uint8_t maxNotes = 100;
public:
	const note happyBirthday[29] = {
		{G3,2}, {G3,2}, {A3,4}, {G3,4}, {C4,4}, {B3,4},
		{pause,4},  {G3,2}, {G3,2}, {A3,4}, {G3,4}, {D4,4}, {C4,4},
		{pause,4}, {G3,2}, {G3,2}, {G4,4}, {E4,4}, {C4,4}, {B3,4}, {A3,8}, 
		{pause,4},  {F4,2}, {F4,2}, {E4,4}, {C4,4}, {D4,4}, {C4,8}, {0,0}
	};

	const note maryHadALittleLamb[26] = {
		{E3, 4}, {D3, 4}, {C3, 4}, {D3, 4}, {E3, 4}, {E3, 4}, {E3, 8}, 
		{D3, 4}, {D3, 4}, {D3, 8}, {E3, 4}, {G3, 4}, {G3, 8},
		{E3, 4}, {D3, 4}, {C3, 4}, {D3, 4}, {E3, 4}, {E3, 4}, {E3, 8}, 
		{D3, 4}, {D3, 4}, {E3, 4}, {D3, 4}, {C3, 8}, {0, 0}
	};

	const note twinkleTwinkleLittleStars[43] = {
		{C3,4}, {C3,4}, {G3,4}, {G3,4}, {A3,4}, {A3,4}, {G3,8}, 
		{F3,4}, {F3,4}, {E3,4}, {E3,4}, {D3,4}, {D3,4}, {C3,8}, 
		{G3,4}, {G3,4}, {F3,4}, {F3,4}, {E3,4}, {E3,4}, {D3,8}, 
		{G3,4}, {G3,4}, {F3,4}, {F3,4}, {E3,4}, {E3,4}, {D3,8}, 
		{C3,4}, {C3,4}, {G3,4}, {G3,4}, {A3,4}, {A3,4}, {G3,8}, 
		{F3,4}, {F3,4}, {E3,4}, {E3,4}, {D3,4}, {D3,4}, {C3,8}, {0,0}
	};
};

Song song;

// Music class functions
// public:
Music::Music(void) {
	songs[0] = song.maryHadALittleLamb;
	songs[1] = song.twinkleTwinkleLittleStars;
	songs[2] = song.happyBirthday;
	songIdx = 0;
}

void Music::nextSong(void) {
	songIdx = (songIdx+1) % songsSize;
}

void Music::playSong(void) {
	uint8_t prevIdx = songIdx;
	uint8_t i=0, j;
	const note* notetab = songs[songIdx];
	

	while (notetab[i].delay) { // delay==0 indicate end of the song
		if (notetab[i].toneIdx == pause) // index = 255 indicate a pause: stop systick
			sound.stop();
		else { // play a regular note
			sound.start(toneTab[notetab[i].toneIdx + sound.octave * majorNotesSize]);
		}
		
		// tempo control: 
		// play current note for specified duration
		for (j=0;j<notetab[i].delay;j++) {
			// if song changed or power off stop playing song
			if (songIdx != prevIdx) {
				sound.stop();
				return;
			}
			else if (sound.getMode() == PIANO) {
				sound.stop();
				songIdx = 0;
				return;
			}
			Delay();
		}
		
		sound.stop();
		i++;  // move to the next note
	}
	
	// pause after each play
	for (j=0;j<15;j++) 
		Delay();
}
