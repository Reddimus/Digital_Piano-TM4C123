// Sound.cpp

#include "Sound.h"

class SysTick {
public:
	void init(void) {
		NVIC_ST_CTRL_R = 0;         // disable SysTick during setup
		NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x20000000; // priority 1      
		NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC|NVIC_ST_CTRL_INTEN;  // enable SysTick with core clock and interrupts
	}

	// Start running systick timer
	void start(void) {
		NVIC_ST_CTRL_R |= NVIC_ST_CTRL_ENABLE;
	}
	// Stop running systick timer
	void stop(void) {
		NVIC_ST_CTRL_R &= ~NVIC_ST_CTRL_ENABLE;
	}

	// update the reload value for current note with with n_value
	void set_Current_Note(unsigned long nValue) {
		NVIC_ST_RELOAD_R = nValue-1;	// update reload value
		NVIC_ST_CURRENT_R = 0;			// any write to current
	}
};
SysTick systick; // global instance of SysTick class

// Sound class functions:
// private:
void Sound::DAC_Init(void) {
	unsigned long volatile delay;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB; // activate port B
	delay = SYSCTL_RCGC2_R;    // allow time to finish activating
	GPIO_PORTB_AMSEL_R &= ~0x3F;      // no analog 
	GPIO_PORTB_PCTL_R &= ~0x00FFFFFF; // regular function
	GPIO_PORTB_DIR_R |= 0x3F;      // make PB5-0 out
	GPIO_PORTB_AFSEL_R &= ~0x3F;   // disable alt funct on PB5-0
	GPIO_PORTB_DEN_R |= 0x3F;      // enable digital I/O on PB5-0
	GPIO_PORTB_DR8R_R |= 0x3F;        // enable 8 mA drive on PB5-0
}

// public:
void Sound::init(void) {
	mode = PIANO;
	octave = 0;
	sineWaveIdx = 0;
	systick.init();
	DAC_Init();
}

void Sound::updateDAC(void) {
	sineWaveIdx = (sineWaveIdx+1)&0x3F;
	DAC = SineWave[sineWaveIdx];
}

void Sound::start(unsigned long period) {
	systick.set_Current_Note(period/samplesSize);
	systick.start();
}

void Sound::stop(void) {
	systick.stop();
}

void Sound::nextOctave(void) {
	octave = (octave+1) % ocativeSize;
}

void Sound::Delay(void) {
	uint32_t volatile time;
	time = 727240*20/91;  // 0.1sec for 16 MHz TM4C123 MCU
	while(time)
		time--;
}

void Sound::setMode(bool m) {
	mode = m;
}

bool Sound::getMode(void) {
	return mode;
}


extern Sound sound;

// SysTick_Handler from startup.s
void SysTick_Handler(void) {
	GPIO_PORTF_DATA_R ^= 0x08;     // toggle PF3, debugging
	sound.updateDAC();
}