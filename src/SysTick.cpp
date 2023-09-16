// SysTick.cpp

#include "SysTick.h"

// Class SysTick
// public:
SysTick::SysTick(void) {
	// Systick initialization | Setup Sytick
	NVIC_ST_CTRL_R = 0;												// disable SysTick during setup
	NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x40000000;		// priority 2
	NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC+NVIC_ST_CTRL_INTEN;
}

// Start running systick timer
void SysTick::start(void) {
	NVIC_ST_CTRL_R |= NVIC_ST_CTRL_ENABLE;
}
// Stop running systick timer
void SysTick::stop(void) {
	NVIC_ST_CTRL_R &= ~NVIC_ST_CTRL_ENABLE;
}

// update the reload value for current note with with n_value
void SysTick::set_Current_Note(uint32_t nValue) {
	NVIC_ST_RELOAD_R = nValue-1;	// update reload value
	NVIC_ST_CURRENT_R = 0;			// any write to current
}


// SysTick_Handler from startup.s
void SysTick_Handler(void) {
	NVIC_ST_CTRL_R &= ~NVIC_ST_CTRL_ENABLE; //clr bit 0
	SPEAKER ^= Speaker_Toggle_Mask; // inverse bit 3
	NVIC_ST_CURRENT_R = 0;      // any write to current clears it
	NVIC_ST_CTRL_R |= NVIC_ST_CTRL_ENABLE;  // set bit 0
}