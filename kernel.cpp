#include "types.h"
#include "gdt.h"
#include "interrupts.h"
#include"driver.h"
#include "keyboard.h"
#include "mouse.h"

void printf(char* str) {
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;
    static uint8_t x = 0, y = 0;
    for(int i=0; str[i] != '\0'; i++) {
        
        switch(str[i]) {
            case '\n':
                x = 0;
                y++;
                break;
            default:
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
        }

        if(x > 80) {
            y++;
            x = 0;
        }

        //If in case the screen is filled
        if(y >= 25) {
            for(y=0; y<=25; y++) {
                for(x=0; x<=80; x++) {
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
                }
            }
            y = 0; x = 0;
        }
    }
}

void printfHex(uint8_t key) {
    char *foo = "00";
    char *hex = "0123456789ABCDEF";
    foo[11] = hex[(key >> 4) & 0xF];
    foo[12] = hex[(key) & 0xF];
    printf(foo);
}

class PrintkeyboardEventHandler : public KeyboardEventHandler {
    public:
        void OnKeyDown(char c) {
            char* foo = " ";
            foo[0] = c;
            printf(foo);
        }
};

class MouseToConsole : public MouseEventHandler {
    int8_t x, y;
    public:
        MouseToConsole() {
            static uint16_t *VideoMemory = (uint16_t *)0xb8000;
            x=40; y=12;
            VideoMemory[80 * 12 + 40] = ((VideoMemory[80 * 12 + 40] & 0xF000) >> 4) | ((VideoMemory[80 * 12 + 40] & 0x0F00) << 4) | (VideoMemory[80 * 12 + 40] & 0x00FF);
        }

        void OnMouseMove(int xoffset, int yoffset) {
            static uint16_t *VideoMemory = (uint16_t *)0xb8000;

            VideoMemory[80 * y + x] = ((VideoMemory[80 * y + x] & 0xF000) >> 4) | ((VideoMemory[80 * y + x] & 0x0F00) << 4) | (VideoMemory[80 * y + x] & 0x00FF);

            x += xoffset;
            if (x < 0)
                x = 0;
            if (x >= 80)
                x = 79;

            y += yoffset;
            if (y < 0)
                y = 0;
            if (y >= 25)
                y = 24;

            VideoMemory[80 * y + x] = ((VideoMemory[80 * y + x] & 0xF000) >> 4) | ((VideoMemory[80 * y + x] & 0x0F00) << 4) | (VideoMemory[80 * y + x] & 0x00FF);
        }
};

extern "C" void kernelMain(void* multiboot_structure, uint32_t magicnumber) {
    printf("Hello World! --- Here is STARBOY \n");

    GlobalDescriptorTable gdt;
    InterruptManager interrupts(&gdt);

    printf("Initializing Hardware, Stage 1 \n");
    
    

    DriverManager drvManager;

        PrintkeyboardEventHandler kbhandler;
        KeyboardDriver keyboard(&interrupts, &kbhandler);
        drvManager.AddDriver(&keyboard);
        printf("Initializing Hardware, Stage 2 \n");

        MouseToConsole mousehandler;
        MouseDriver mouse(&interrupts, &mousehandler);
        drvManager.AddDriver(&mouse);
        printf("Initializing Hardware, Stage 3 \n");

        drvManager.ActivateAll();

    interrupts.Activate();
    
    // XeOS never stops :D
    while(1);
}
