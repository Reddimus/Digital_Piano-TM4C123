#ifndef SWITCH_H
#define SWITCH_H

#define SW1 0x10
#define SW2 0x01

#include "tm4c123gh6pm.h"
#include "Music.h"

class Switch {
public:
	Switch(void);
};

extern "C" {
	void GPIOPortF_Handler(void);
}

#endif
