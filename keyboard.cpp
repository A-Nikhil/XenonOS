#include "keyboard.h"

KeyboardEventHandler::KeyboardEventHandler()
{
}
void KeyboardEventHandler::OnKeyDown(char)
{
}
void KeyboardEventHandler::OnKeyUp(char)
{
}
KeyboardDriver::KeyboardDriver(InterruptManager* manager, KeyboardEventHandler *handler)
: InterruptHandler(manager, 0x21),
dataport(0x60),
commandport(0x64)
{
    this->handler = handler;
}
KeyboardDriver::~KeyboardDriver()
{
}
void printf(char*);
void printfHex(uint8_t);
void KeyboardDriver::Activate()
{
    while(commandport.Read() & 0x1)
        dataport.Read();
     commandport.Write(0xae); // activate interrupts
     commandport.Write(0x20); // command 0x20 = read controller command byte
     uint8_t status = (dataport.Read() | 1) & ~0x10;
     commandport.Write(0x60); // command 0x60 = set controller command byte
     dataport.Write(status);
    dataport.Write(0xf4);
}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t key = dataport.Read();
    
    if(handler == 0)
        return esp;
    
    if(key < 0x80)
    {
        switch(key)
        {
            
            default:
            {
                printf("KEYBOARD 0x");
                printfHex(key);
                 break;
            }
        }
     }
     return esp;
}
