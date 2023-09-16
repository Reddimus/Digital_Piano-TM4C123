#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>
#include "tm4c123gh6pm.h"

#define SPEAKER (*((volatile unsigned long *)0x40004020))
#define Speaker_Toggle_Mask	0x00000008

class SysTick {
public:
	SysTick(void);
	void start(void);
	void stop(void);
	void set_Current_Note(uint32_t nValue);
};

extern "C" {
	void SysTick_Handler(void);
}

#endif
