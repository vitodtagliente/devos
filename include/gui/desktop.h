 
#ifndef __DESKTOP_H
#define __DESKTOP_H

#include <gui/widget.h>
#include <drivers/mouse.h>
#include <drivers/vga.h>
        
class Desktop : public CompositeWidget, public MouseEventHandler
{
    protected:
        unsigned int MouseX;
        unsigned int MouseY;
        
    public:
        Desktop(int w, int h,
            unsigned char r, unsigned char g, unsigned char b);
        ~Desktop();
        
        void Draw(VideoGraphicsArray* gc);
        
        void OnMouseDown(unsigned char button);
        void OnMouseUp(unsigned char button);
        void OnMouseMove(int x, int y);
};
       
#endif