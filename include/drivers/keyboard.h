#ifndef __XENONOS__DRIVERS__KEYBOARD_H
#define __XENONOS__DRIVERS__KEYBOARD_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>
#include <hardwarecommunication/port.h>

namespace xenonos {
    namespace drivers {
        class KeyboardEventHandler {
            public:
                KeyboardEventHandler();
                virtual void OnKeyDown(char);
                virtual void OnKeyUp(char);
        };

        class KeyboardDriver : public xenonos::hardwarecommunication::InterruptHandler, public Driver {
            xenonos::hardwarecommunication::Port8BitSlow dataport;
            xenonos::hardwarecommunication::Port8BitSlow commandport;
            KeyboardEventHandler* handler;
            public:
                KeyboardDriver(xenonos::hardwarecommunication::InterruptManager* manager, KeyboardEventHandler *handler);
                ~KeyboardDriver();
                virtual xenonos::common::uint32_t HandleInterrupt(xenonos::common::uint32_t esp);
                virtual void Activate();
        };
    }
}
#endif