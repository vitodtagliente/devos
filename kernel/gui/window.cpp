#include <gui/window.h>

Window::Window(Widget* parent,
            int x, int y, int w, int h,
            unsigned char r, unsigned char g, unsigned char b)
: CompositeWidget(parent, x,y,w,h, r,g,b)
{
    Dragging = false;
}

Window::~Window()
{
}

void Window::OnMouseDown(int x, int y, unsigned char button)
{
    Dragging = button == 1;
    CompositeWidget::OnMouseDown(x,y,button);
}

void Window::OnMouseUp(int x, int y, unsigned char button)
{
    Dragging = false;
    CompositeWidget::OnMouseUp(x,y,button);
}

void Window::OnMouseMove(int oldx, int oldy, int newx, int newy)
{
    if(Dragging)
    {
        this->x += newx-oldx;
        this->y += newy-oldy;
    }
    CompositeWidget::OnMouseMove(oldx,oldy,newx, newy);

}

    
