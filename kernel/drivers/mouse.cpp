
#include <drivers/mouse.h>

MouseEventHandler::MouseEventHandler()
{
}

void MouseEventHandler::OnEnable()
{
}

void MouseEventHandler::OnMouseDown(unsigned char button)
{
}

void MouseEventHandler::OnMouseUp(unsigned char button)
{
}

void MouseEventHandler::OnMouseMove(int x, int y)
{
}

// ###################

Mouse::Mouse(InterruptManager* manager, MouseEventHandler* handler): 
    InterruptHandler(manager, 0x2C),
    dataport(0x60),
    commandport(0x64)
{
    this->handler = handler;
}

Mouse::~Mouse()
{
}

void Mouse::Enable()
{
    offset = 0;
    buttons = 0;

    if(handler != 0)
        handler->OnEnable();
    
    commandport.Write(0xA8);
    commandport.Write(0x20); // command 0x60 = read controller command byte
    unsigned char status = dataport.Read() | 2;
    commandport.Write(0x60); // command 0x60 = set controller command byte
    dataport.Write(status);

    commandport.Write(0xD4);
    dataport.Write(0xF4);
    dataport.Read();        
}

unsigned int Mouse::HandleInterrupt(unsigned int esp)
{
    unsigned char status = commandport.Read();
    if (!(status & 0x20))
        return esp;

    buffer[offset] = dataport.Read();
    
    if(handler == 0)
        return esp;
    
    offset = (offset + 1) % 3;

    if(offset == 0)
    {
        if(buffer[1] != 0 || buffer[2] != 0)
        {
            handler->OnMouseMove((unsigned char)buffer[1], -((unsigned char)buffer[2]));
        }

        for(unsigned char i = 0; i < 3; i++)
        {
            if((buffer[0] & (0x1<<i)) != (buttons & (0x1<<i)))
            {
                if(buttons & (0x1<<i))
                    handler->OnMouseUp(i+1);
                else
                    handler->OnMouseDown(i+1);
            }
        }
        buttons = buffer[0];
    }
    
    return esp;
}
