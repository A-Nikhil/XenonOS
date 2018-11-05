#ifndef __MOUSE_H
#define __MOUSE_H

#include "types.h"
#include "interrupts.h"
#include "driver.h"
#include "port.h"

class MouseDriver : public InterruptHandler, public Driver{
    Port8BitSlow dataport;
    Port8BitSlow commandport;
    uint8_t buffer[3];
    uint8_t offset;
    uint8_t buttons;
    int8_t x,y;
    public:
        MouseDriver(InterruptManager* manager);
        ~MouseDriver();
        virtual uint32_t HandleInterrupt(uint32_t esp);
		virtua void Activate();
};

#endif
