
#ifndef __KEYBOARD_H_
#define __KEYBOARD_H_

#include <interrupts.h>
#include <port.h>
#include <driver.h>

class KeyboardEventHandler
{
    public:
        KeyboardEventHandler();

        virtual void OnKeyDown(char);
        virtual void OnKeyUp(char);
};

class Keyboard : public InterruptHandler, public Driver
{
        Port8Bit dataport;
        Port8Bit commandport;
        
        KeyboardEventHandler* handler;
        
    public:
        Keyboard(InterruptManager* manager, KeyboardEventHandler *handler);
        ~Keyboard();
        virtual unsigned int HandleInterrupt(unsigned int esp);
        virtual void Enable();
};

#endif