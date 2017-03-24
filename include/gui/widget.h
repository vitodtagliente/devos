 
#ifndef __WIDGET_H
#define __WIDGET_H

#include <drivers/keyboard.h>
#include <drivers/vga.h>

class Widget : public KeyboardEventHandler
{
    protected:
        Widget* parent;
        int x;
        int y;
        int w;
        int h;
        
        unsigned char r;
        unsigned char g;
        unsigned char b;
        bool Focussable;

    public:

        Widget(Widget* parent,
                int x, int y, int w, int h,
                unsigned char r, unsigned char g, unsigned char b);
        ~Widget();
        
        virtual void GetFocus(Widget* widget);
        virtual void ModelToScreen(int &x, int& y);
        virtual bool ContainsCoordinate(int x, int y);
        
        virtual void Draw(VideoGraphicsArray* gc);
        virtual void OnMouseDown(int x, int y, unsigned char button);
        virtual void OnMouseUp(int x, int y, unsigned char button);
        virtual void OnMouseMove(int oldx, int oldy, int newx, int newy);
};


class CompositeWidget : public Widget
{
    private:
        Widget* children[100];
        int numChildren;
        Widget* focussedChild;
        
    public:
        CompositeWidget(Widget* parent,
                int x, int y, int w, int h,
                unsigned char r, unsigned char g, unsigned char b);
        ~CompositeWidget();            
        
        virtual void GetFocus(Widget* widget);
        virtual bool AddChild(Widget* child);
        
        virtual void Draw(VideoGraphicsArray* gc);
        virtual void OnMouseDown(int x, int y, unsigned char button);
        virtual void OnMouseUp(int x, int y, unsigned char button);
        virtual void OnMouseMove(int oldx, int oldy, int newx, int newy);
        
        virtual void OnKeyDown(char);
        virtual void OnKeyUp(char);
};

#endif