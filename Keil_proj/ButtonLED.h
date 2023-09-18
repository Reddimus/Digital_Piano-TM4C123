#ifndef BUTTONSLEDS_H
#define BUTTONSLEDS_H

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Music.h"
#include "Piano.h"

class ButtonsLEDs {
private:
	void GPIOPortF_Init(void);
	void GPIOPortD_Init(void);
public:
	void init(void);
};

extern "C" {
	void GPIOPortF_Handler(void);
	void GPIOPortD_Handler(void);
}

#endif