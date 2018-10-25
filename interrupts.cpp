#include "interrupts.h"

void printf(char* str);

InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];

void InterruptManager::SetInterruptDescriptorTableEntry(
	uint8_t InterruptNumber,
	uint16_t codeSegmentSelectorOffset,
	void (*handler) (),
	uint8_t DescriptorPrivilegeLevel,
	uint8_t DescriptorType
	) {
	const uint8_t IDT_DESC_PRESENT = 0x80;
	interruptDescriptorTable[InterruptNumber].handlerAddressLowBits = ((uint32_t)handler) & 0xFFFF;
	interruptDescriptorTable[InterruptNumber].handlerAddressHighBits = ((uint32_t)handler >> 16) & 0xFFFF;
	interruptDescriptorTable[InterruptNumber].gdt_codeSegmentSelector = codeSegmentSelectorOffset;
	interruptDescriptorTable[InterruptNumber].reserved = 0;
	interruptDescriptorTable[InterruptNumber].access = IDT_DESC_PRESENT | DescriptorType | ((DescriptorPrivilegeLevel&3) << 5);
}

InterruptManager::InterruptManager(GlobalDescriptorTable* gdt)
: picMasterCommand(0x20),
  picMasterData(0x21),
  picSlaveCommand(0xA0),
  picSlaveData(0xA1)
 {
	uint16_t codeSegment = gdt->CodeSegmentSelector();
	const uint8_t IDT_INTERRUPT_GATE = 0xE;

	for(uint16_t i=0; i<256; i++) {
		SetInterruptDescriptorTableEntry(i, codeSegment, &IgnoreInterruptRequest, 0, IDT_INTERRUPT_GATE);
	}

	SetInterruptDescriptorTableEntry(0x20, codeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
	SetInterruptDescriptorTableEntry(0x21, codeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);

	picMasterCommand.Write(0x11);
	picSlaveCommand.Write(0x11);

	picMasterData.Write(0x20);
	picSlaveData.Write(0x28);
	
	picMasterData.Write(0x04);
	picSlaveData.Write(0x02);
	
	picMasterData.Write(0x01);
	picSlaveData.Write(0x01);
	
	picMasterData.Write(0x00);
	picSlaveData.Write(0x00);


	interruptDescriptorTablePointer idt;
	idt.size = 256 * sizeof(GateDescriptor) - 1;
	idt.base = (uint32_t)interruptDescriptorTable;
	asm volatile("lidt %0" : : "m" (idt));
}

InterruptManager::~InterruptManager() {}

// Tells the CPU to start sending interrupts
void InterruptManager::Activate() {
	asm("sti");
}

uint32_t InterruptManager::handleInterrupt(uint8_t interruptNumber, uint32_t esp) {
	printf("INTERRUPT TESTING");
	return esp;
}