// Switch.cpp
#include "Switch.h"
extern Music music;

// class Switch methods
// public:
Switch::Switch(void) {
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


// ISR for GPIOPortF_Handler from startup.s
extern void GPIOPortF_Handler(void){
	if(GPIO_PORTF_RIS_R & SW1 && music.isOn()) {
		GPIO_PORTF_ICR_R = SW1;			// acknowledge flag4
		music.turnOff();
	}
	else if(GPIO_PORTF_RIS_R & SW1 && !music.isOn()) {
		GPIO_PORTF_ICR_R = SW1;
		music.turnOn();
	}

	if(GPIO_PORTF_RIS_R & SW2) {
		GPIO_PORTF_ICR_R = SW2;			// acknowledge flag0
		music.nextSong();
	}
}
