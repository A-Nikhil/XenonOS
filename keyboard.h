#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "types.h"
#include "interrupts.h"
#include "drivers.h"
#include "port.h"

class KeyboardDriver : public InterruptHandler, public Driver {
    Port8BitSlow dataport;
    Port8BitSlow commandport;
    public:
        KeyboardDriver(InterruptManager* manager);
        ~KeyboardDriver();
        virtual uint32_t HandleInterrupt(uint32_t esp);
	virtual void Actvate();
};

#endif
