.set IRQ_BASE, 0x20

.section .text

# interrupt call number, required for handling
.extern _ZN7xenonos21hardwarecommunication16InterruptManager15handleInterruptEhj

.global _ZN7xenonos21hardwarecommunication16InterruptManager22IgnoreInterruptRequestEv

.macro HandleException num
.global _ZN7xenonos21hardwarecommunication16InterruptManager16HandleException\num\()Ev
_ZN7xenonos21hardwarecommunication16InterruptManager16HandleException\num\()Ev:
	movb $\num, (interruptnumber)
	jmp int_bottom
.endm

.macro HandleInterruptRequest num
.global _ZN7xenonos21hardwarecommunication16InterruptManager26HandleInterruptRequest\num\()Ev
_ZN7xenonos21hardwarecommunication16InterruptManager26HandleInterruptRequest\num\()Ev:
	movb $\num + IRQ_BASE, (interruptnumber)
	jmp int_bottom
.endm

HandleInterruptRequest 0x00
HandleInterruptRequest 0x01
HandleInterruptRequest 0x0C

int_bottom:
	
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs

	push %esp
	push (interruptnumber)
	call _ZN7xenonos21hardwarecommunication16InterruptManager15handleInterruptEhj
	movl %eax, %esp

	popl %gs
	popl %fs
	popl %es
	popl %ds
	popa

	_ZN7xenonos21hardwarecommunication16InterruptManager22IgnoreInterruptRequestEv:

	# Tells the processor that interrupt handling is done 
	# and it can return to what it was doing earlier
	iret

data:
	interruptnumber: .byte 0
