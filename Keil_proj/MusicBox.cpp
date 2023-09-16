// MusicBox.cpp

#include "tm4c123gh6pm.h"
#include "Music.h"
#include "SysTick.h"
#include "Switch.h"

// Treat the specified functions with C linkage from startup.s to disable name mangling
extern "C" {
    void EnableInterrupts(void);
    void DisableInterrupts(void);
    void WaitForInterrupt(void);
}

// Global class instance
Music music;
SysTick systick;
Switch sw;

int main(void) {
	DisableInterrupts();
	EnableInterrupts();  // SysTick uses interrupts
	
	while(true) {
		if (music.isOn())
			music.playSongNotes();
		else
			WaitForInterrupt();
	}
}
