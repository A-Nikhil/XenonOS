#ifndef __XENONOS__DRIVERS__MOUSE_H
#define __XENONOS__DRIVERS__MOUSE_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>
#include <hardwarecommunication/port.h>

namespace xenonos {
    namespace drivers {
        class MouseEventHandler {

            public:
                MouseEventHandler();
                virtual void OnActivate();
                virtual void OnMouseDown(xenonos::common::uint8_t button);
                virtual void OnMouseUp(xenonos::common::uint8_t button);
                virtual void OnMouseMove(int x, int y);
        };

        class MouseDriver : public xenonos::hardwarecommunication::InterruptHandler, public Driver {
            xenonos::hardwarecommunication::Port8BitSlow dataport;
            xenonos::hardwarecommunication::Port8BitSlow commandport;
            xenonos::common::uint8_t buffer[3];
            xenonos::common::uint8_t offset;
            xenonos::common::uint8_t buttons;

            MouseEventHandler* handler;
            public:
                MouseDriver(xenonos::hardwarecommunication::InterruptManager* manager, MouseEventHandler* handler);
                ~MouseDriver();
                virtual xenonos::common::uint32_t HandleInterrupt(xenonos::common::uint32_t esp);
                virtual void Activate();
        };
    }
}

#endif