#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "types.h"
#include "interrupts.h"
#include "drivers.h"
#include "port.h"


class KeyboardEventHandler{
	public:
		KeyboardEventhandler(); //Have methods for on key down, on key up
		virtual void OnKeyDown(char);
		virtual void OnKeyUp(char);
};

class KeyboardDriver : public InterruptHandler, public Driver {
    Port8BitSlow dataport;
    Port8BitSlow commandport;
    KeyboardEventHandler* handler;
    public:
        KeyboardDriver(InterruptManager* manager, KeyboardEventHandler *handler);
        ~KeyboardDriver();
        virtual uint32_t HandleInterrupt(uint32_t esp);
	virtual void Actvate();
};

#endif
