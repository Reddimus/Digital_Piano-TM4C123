// Music.cpp

#include "Music.h"
extern SysTick systick;

class Song {
private:
	const uint8_t pause = 255, maxNotes = 100;
	// Index for notes used in music scores
	enum noteNames { C4, D4, E4, F4, G4, A4, B4, C5, D5, E5, F5, G5, A5, B5, C6, D6, E6, F6, G6 };
public:
	const note happyBirthday[29] = {
		// so   so   la   so   doe' ti
		{G4,2}, {G4,2}, {A4,4}, {G4,4}, {C5,4}, {B4,4},
		// pause so   so   la   so   ray' doe'
		{pause,4},  {G4,2}, {G4,2}, {A4,4}, {G4,4}, {D5,4}, {C5,4},
		// pause so   so   so'  mi'  doe' ti   la
		{pause,4}, {G4,2}, {G4,2}, {G5,4}, {E5,4}, {C5,4}, {B4,4}, {A4,8}, 
		// pause fa'  fa'   mi'  doe' ray' doe'  stop
		{pause,4},  {F5,2}, {F5,2}, {E5,4}, {C5,4}, {D5,4}, {C5,8}, {0,0}};

	const note maryHadALittleLamb[26] = {
		{E4, 4}, {D4, 4}, {C4, 4}, {D4, 4}, {E4, 4}, {E4, 4}, {E4, 8}, 
		{D4, 4}, {D4, 4}, {D4, 8}, {E4, 4}, {G4, 4}, {G4, 8},
		{E4, 4}, {D4, 4}, {C4, 4}, {D4, 4}, {E4, 4}, {E4, 4}, {E4, 8}, 
		{D4, 4}, {D4, 4}, {E4, 4}, {D4, 4}, {C4, 8}, {0, 0}};

	const note twinkleTwinkleLittleStars[43] = {
		{C4,4}, {C4,4}, {G4,4}, {G4,4}, {A4,4}, {A4,4}, {G4,8}, 
		{F4,4}, {F4,4}, {E4,4}, {E4,4}, {D4,4}, {D4,4}, {C4,8}, 
		{G4,4}, {G4,4}, {F4,4}, {F4,4}, {E4,4}, {E4,4}, {D4,8}, 
		{G4,4}, {G4,4}, {F4,4}, {F4,4}, {E4,4}, {E4,4}, {D4,8}, 
		{C4,4}, {C4,4}, {G4,4}, {G4,4}, {A4,4}, {A4,4}, {G4,8}, 
		{F4,4}, {F4,4}, {E4,4}, {E4,4}, {D4,4}, {D4,4}, {C4,8}, {0,0}};

	bool isSongToneIdxPaused(uint8_t idx) {
		return idx == pause;
	}
};

// Music class functions
// private:
void Music::GPIOPortA_Init(void) {
	volatile uint32_t delay;
	SYSCTL_RCGC2_R |= 0x01;				// 1) activate clock for Port A
	delay = SYSCTL_RCGC2_R;				// allow time for clock to start
										// 2) no need to unlock PA3
	GPIO_PORTA_PCTL_R &= ~0x00000F00;	// 3) regular GPIO
	GPIO_PORTA_AMSEL_R &= ~0x08;		// 4) disable analog function on PA3
	GPIO_PORTA_DIR_R |= 0x08;			// 5) set direction to output
	GPIO_PORTA_AFSEL_R &= ~0x08;		// 6) regular port function
	GPIO_PORTA_DEN_R |= 0x08;			// 7) enable digital port
	GPIO_PORTA_DR8R_R |= 0x08;			// 8) optional: enable 8 mA drive on PA3 to increase the voice volumn
}

void Music::Delay(void) {
	uint32_t volatile time;
	time = 727240*20/91;  // 0.1sec for 16 MHz TM4C123 MCU
	while(time)
		time--;
}

Song song;

// public:
Music::Music(void) {
	songs[0] = song.happyBirthday;
	songs[1] = song.maryHadALittleLamb;
	songs[2] = song.twinkleTwinkleLittleStars;
	songIdx = 0;
	play = false;
	Music::GPIOPortA_Init();
}

void Music::nextSong(void) {
	if (0 <= songIdx && songIdx < songsSize-2)
		songIdx++;
	else
		songIdx = 0;
}

bool Music::isOn(void) {
	return play;
}

void Music::turnOff(void) {
	play = false;
	songIdx = 0;
}

void Music::turnOn(void) {
	play = true;
}

void Music::playSongNotes(void) {
	uint8_t prevIdx = songIdx;
	uint8_t i=0, j;
	const note* notetab = songs[songIdx];
	

	while (notetab[i].delay) { // delay==0 indicate end of the song
		if (song.isSongToneIdxPaused(notetab[i].toneIdx)) // index = 255 indicate a pause: stop systick
			systick.stop(); // silence tone, turn off SysTick timer
		else { // play a regular note
			systick.set_Current_Note(toneTab[notetab[i].toneIdx]);
			systick.start();
		}
		
		// tempo control: 
		// play current note for specified duration
		for (j=0;j<notetab[i].delay;j++) {
			// if song changed or power off stop playing song
			if (songIdx != prevIdx || !isOn()) {
				systick.stop();
				return;
			}
			Delay();
		}
		
		systick.stop();
		i++;  // move to the next note
	}
	
	// pause after each play
	for (j=0;j<15;j++) 
		Delay();
}
