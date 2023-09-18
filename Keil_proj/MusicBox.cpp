// MusicBox.cpp

#include "Sound.h"
#include "Music.h"
#include "Piano.h"
#include "ButtonLED.h"

// Treat the specified functions with C linkage from startup.s to disable name mangling
extern "C" {
    void EnableInterrupts(void);
    void DisableInterrupts(void);
    void WaitForInterrupt(void);
}

// Global class instance
Sound sound;
Music music;
Piano piano;
ButtonsLEDs buttonsLEDs;

int main(void) {
	DisableInterrupts();
	sound.init();
	buttonsLEDs.init();
	EnableInterrupts();  // SysTick uses interrupts
	
	while(true) {
		if (sound.getMode() == PIANO)
			WaitForInterrupt();
		else if (sound.getMode() == MUSIC)
			music.playSong();
	}
}
