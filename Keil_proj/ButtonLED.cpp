// ButtonLED.cpp

#define SW1 0x10
#define SW2 0x01
#define PD0 0x01
#define PD1 0x02
#define PD2 0x04
#define PD3 0x08

#include "ButtonLED.h"

extern Sound sound;
extern Piano piano;
extern Music music;

// ButtonLED class functions:
// private:
void ButtonsLEDs::GPIOPortF_Init(void) {
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF; // activate port F
	while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOF)!=SYSCTL_RCGC2_GPIOF);

	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;	// unlock GPIO Port F
	GPIO_PORTF_CR_R |= 0x1F;			// allow changes to PF4-0
	GPIO_PORTF_AMSEL_R &= ~0x1F;		// disable analog on PF4-0
	GPIO_PORTF_PCTL_R &= ~0x000FFFFF;	// PCTL GPIO on PF4-0
	GPIO_PORTF_DIR_R &= ~0x11;			// PF4,PF0 in, PF3-1 out
	GPIO_PORTF_AFSEL_R &= ~0x1F;		// disable alt funct on PF4-0
	GPIO_PORTF_PUR_R |= 0x11;			// enable pull-up on PF0 and PF4
	GPIO_PORTF_DEN_R |= 0x1F;			// enable digital I/O on PF4-0
	GPIO_PORTF_IS_R &= ~0x11;			// PF4,PF0 is edge-sensitive
	GPIO_PORTF_IBE_R &= ~0x11;			// PF4,PF0 is not both edges
	GPIO_PORTF_IEV_R &= ~0x11;			// PF4,PF0 falling edge event
	GPIO_PORTF_ICR_R = 0x11;			// clear flag0,4
	GPIO_PORTF_IM_R |= 0x11;			// enable interrupt on PF0,PF4
	NVIC_PRI7_R = (NVIC_PRI7_R&0xFF1FFFFF)|0x00400000; // (g) bits:23-21 for PORTF, set priority to 2
	NVIC_EN0_R |= 0x40000000;			// (h) enable interrupt 30 in NVIC
}

void ButtonsLEDs::GPIOPortD_Init(void) {
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD; // activate port D
	while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOD)!=SYSCTL_RCGC2_GPIOD);

	GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;	// unlock GPIO Port D
	GPIO_PORTD_CR_R |= 0x1F;			// allow changes to PD3-0
	GPIO_PORTD_AMSEL_R &= ~0x1F;		// disable analog on PD3-0
	GPIO_PORTD_PCTL_R &= ~0x000FFFFF;	// PCTL GPIO on PD4-0
	GPIO_PORTD_DIR_R &= ~0x1F;			// PD4,PD0 in, PD3-1 out
	GPIO_PORTD_AFSEL_R &= ~0x1F;		// disable alt funct on PD4-0
	GPIO_PORTD_PUR_R |= 0x1F;			// enable pull-up on PF0 and PD4
	GPIO_PORTD_DEN_R |= 0x1F;			// enable digital I/O on PD4-0
	GPIO_PORTD_IS_R &= ~0x1F;			// PD4,PD0 is edge-sensitive
	GPIO_PORTD_IBE_R &= ~0x1F;			// PD4,PD0 is not both edges
	GPIO_PORTD_IEV_R &= ~0x1F;			// PD4,PD0 falling edge event
	GPIO_PORTD_ICR_R = 0x1F;			// clear flag0,4
	GPIO_PORTD_IM_R |= 0x1F;			// enable interrupt on PD0,PD4
	NVIC_PRI0_R = (NVIC_PRI0_R&0x1FFFFFFF)|0x80000000; // PORTD priority bits 31-29, set priority to 3
	NVIC_EN0_R |= 0x00000008; 			// (h) enable interrupt in NVIC
}

// public:
void ButtonsLEDs::init(void) {
	GPIOPortF_Init();
	GPIOPortD_Init();
}


// GPIO Handlers from startup.s:
void GPIOPortD_Handler(void){  
  // simple debouncing code: generate 20ms to 30ms delay
	for (uint32_t time=0;time<72724;time++);
	if(sound.getMode() == PIANO) {

		if(GPIO_PORTD_RIS_R&PD0){	// if pd0 piano key pressed
			GPIO_PORTD_ICR_R = PD0;	// acknowledge flag0
			piano.playNoteC();
		}
		if(GPIO_PORTD_RIS_R&PD1){	// if pd1 piano key pressed
			GPIO_PORTD_ICR_R = PD1;	// acknowledge flag1
			piano.playNoteD();
		}
		if(GPIO_PORTD_RIS_R&PD2){	// if pd2 piano key pressed
			GPIO_PORTD_ICR_R = PD2;	// acknowledge flag2
			piano.playNoteE();
		}
		if(GPIO_PORTD_RIS_R&PD3){	// if pd3 piano key pressed
			GPIO_PORTD_ICR_R = PD3;	// acknowledge flag3
			piano.playNoteF();
		}			
	}	 
}

void GPIOPortF_Handler(void){
	// simple debouncing code: generate 20ms to 30ms delay
	for (uint32_t time=0;time<72724;time++);

	if(GPIO_PORTF_RIS_R & SW1) { 			//if sw1 pressed
		GPIO_PORTF_ICR_R = SW1; 			//ackowledge flag for sw1
		sound.setMode(!sound.getMode());	//toggle
	}

	if(GPIO_PORTF_RIS_R & SW2) {			//if sw2 pressed
		GPIO_PORTF_ICR_R = SW2;				// acknowledge flag for SW2

		if(sound.getMode() == PIANO)
			sound.nextOctave();
		else if(sound.getMode() == MUSIC)
			music.nextSong();
	}
}