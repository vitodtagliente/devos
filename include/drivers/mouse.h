
#ifndef __MOUSE_H
#define __MOUSE_H

#include <interrupts.h>
#include <port.h>
#include <driver.h>

class MouseEventHandler
{
    public:
        MouseEventHandler();

        virtual void OnEnable();
        virtual void OnMouseDown(unsigned char button);
        virtual void OnMouseUp(unsigned char button);
        virtual void OnMouseMove(int x, int y);
};

class MouseToConsoleEventHandler : public MouseEventHandler
{
    unsigned char x, y;
    
    public:
        
        MouseToConsoleEventHandler()
        {
            unsigned short* VideoMemory = (unsigned short*)0xb8000;
            x = 40;
            y = 12;
            VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                                | (VideoMemory[80*y+x] & 0xF000) >> 4
                                | (VideoMemory[80*y+x] & 0x00FF);        
        }
        
        virtual void OnMouseMove(int xoffset, int yoffset)
        {
            static unsigned short* VideoMemory = (unsigned short*)0xb8000;
            VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                                | (VideoMemory[80*y+x] & 0xF000) >> 4
                                | (VideoMemory[80*y+x] & 0x00FF);

            x += xoffset;
            if(x >= 80) x = 79;
            if(x < 0) x = 0;
            y += yoffset;
            if(y >= 25) y = 24;
            if(y < 0) y = 0;

            VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                                | (VideoMemory[80*y+x] & 0xF000) >> 4
                                | (VideoMemory[80*y+x] & 0x00FF);
        }
        
};

class Mouse : public InterruptHandler, public Driver
{
    Port8Bit dataport;
    Port8Bit commandport;
    unsigned char buffer[3];
    unsigned char offset;
    unsigned char buttons;

    MouseEventHandler* handler;

    public:
        Mouse(InterruptManager* manager, MouseEventHandler* handler);
        ~Mouse();
        virtual unsigned int HandleInterrupt(unsigned int esp);
        virtual void Enable();
};
    
#endif
