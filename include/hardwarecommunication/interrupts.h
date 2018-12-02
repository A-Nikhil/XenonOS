#ifndef __XENONOS__HARDWARECOMMUNICATION__INTERRUPTS_H
#define __XENONOS__HARDWARECOMMUNICATION__INTERRUPTS_H

#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <gdt.h>

namespace xenonos {
	namespace hardwarecommunication {
		class InterruptManager;

		class InterruptHandler {
			protected:
				xenonos::common::uint8_t interruptNumber;
				InterruptManager* interruptManager;

				InterruptHandler(xenonos::common::uint8_t interruptNumber, InterruptManager* interruptManager);
				~InterruptHandler();

			public:
				virtual xenonos::common::uint32_t HandleInterrupt(xenonos::common::uint32_t esp);
		};

		class InterruptManager {
			friend class InterruptHandler;
			protected:
				static InterruptManager* ActiveInterruptManager;
				InterruptHandler* handlers[256];

				struct GateDescriptor {
					xenonos::common::uint16_t handlerAddressLowBits;
					xenonos::common::uint16_t gdt_codeSegmentSelector;
					xenonos::common::uint8_t reserved;
					xenonos::common::uint8_t access;
					xenonos::common::uint16_t handlerAddressHighBits;

				} __attribute__((packed));
				static GateDescriptor interruptDescriptorTable[256];

				struct interruptDescriptorTablePointer {
					xenonos::common::uint16_t size;
					xenonos::common::uint32_t base;
				} __attribute__ ((packed));

				static void SetInterruptDescriptorTableEntry(
					xenonos::common::uint8_t InterruptNumber,
					xenonos::common::uint16_t codeSegmentSelectorOffset,
					void (*handler) (),
					xenonos::common::uint8_t DescriptorPrivilegeLevel,
					xenonos::common::uint8_t DescriptorType
				);

				Port8BitSlow picMasterCommand;
				Port8BitSlow picMasterData;
				Port8BitSlow picSlaveCommand;
				Port8BitSlow picSlaveData;

			public:
				InterruptManager(xenonos::GlobalDescriptorTable* gdt);
				~InterruptManager();

				void Activate();
				void Deactivate();

				
				static xenonos::common::uint32_t handleInterrupt(xenonos::common::uint8_t interruptNumber, xenonos::common::uint32_t esp);
				xenonos::common::uint32_t DoHandleInterrupt(xenonos::common::uint8_t interruptNumber, xenonos::common::uint32_t esp);

				static void IgnoreInterruptRequest();
				static void HandleInterruptRequest0x00();
				static void HandleInterruptRequest0x01();
				static void HandleInterruptRequest0x0C();
		};
	}
}

#endif