 
#ifndef __WINDOW_H
#define __WINDOW_H

#include <gui/widget.h>
#include <drivers/mouse.h>
 
class Window : public CompositeWidget
{ 
    protected:
        bool Dragging;
        
    public:
        Window(Widget* parent,
                int x, int y, int w, int h,
                unsigned char r, unsigned char g, unsigned char b);
        ~Window();

        void OnMouseDown(int x, int y, unsigned char button);
        void OnMouseUp(int x, int y, unsigned char button);
        void OnMouseMove(int oldx, int oldy, int newx, int newy);
        
};

#endif