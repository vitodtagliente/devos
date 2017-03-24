#include <gui/widget.h>

Widget::Widget(Widget* parent, int x, int y, int w, int h,
                               unsigned char r, unsigned char g, unsigned char b)
: KeyboardEventHandler()
{
    this->parent = parent;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->r = r;
    this->g = g;
    this->b = b;
    this->Focussable = true;
}

Widget::~Widget()
{
}
            
void Widget::GetFocus(Widget* widget)
{
    if(parent != 0)
        parent->GetFocus(widget);
}

void Widget::ModelToScreen(int &x, int& y)
{
    if(parent != 0)
        parent->ModelToScreen(x,y);
    x += this->x;
    y += this->y;
}
            
void Widget::Draw(VideoGraphicsArray* gc)
{
    int X = 0;
    int Y = 0;
    ModelToScreen(X,Y);
    gc->FillRectangle(X,Y,w,h, r,g,b);
}

void Widget::OnMouseDown(int x, int y, unsigned char button)
{
    if(Focussable)
        GetFocus(this);
}

bool Widget::ContainsCoordinate(int x, int y)
{
    return this->x <= x && x < this->x + this->w
        && this->y <= y && y < this->y + this->h;
}

void Widget::OnMouseUp(int x, int y, unsigned char button)
{
}

void Widget::OnMouseMove(int oldx, int oldy, int newx, int newy)
{
}









CompositeWidget::CompositeWidget(Widget* parent,
                   int x, int y, int w, int h,
                   unsigned char r, unsigned char g, unsigned char b)
: Widget(parent, x,y,w,h, r,g,b)
{
    focussedChild = 0;
    numChildren = 0;
}

CompositeWidget::~CompositeWidget()
{
}
            
void CompositeWidget::GetFocus(Widget* widget)
{
    this->focussedChild = widget;
    if(parent != 0)
        parent->GetFocus(this);
}

bool CompositeWidget::AddChild(Widget* child)
{
    if(numChildren >= 100)
        return false;
    children[numChildren++] = child;
    return true;
}


void CompositeWidget::Draw(VideoGraphicsArray* gc)
{
    Widget::Draw(gc);
    for(int i = numChildren-1; i >= 0; --i)
        children[i]->Draw(gc);
}


void CompositeWidget::OnMouseDown(int x, int y, unsigned char button)
{
    for(int i = 0; i < numChildren; ++i)
        if(children[i]->ContainsCoordinate(x - this->x, y - this->y))
        {
            children[i]->OnMouseDown(x - this->x, y - this->y, button);
            break;
        }
}

void CompositeWidget::OnMouseUp(int x, int y, unsigned char button)
{
    for(int i = 0; i < numChildren; ++i)
        if(children[i]->ContainsCoordinate(x - this->x, y - this->y))
        {
            children[i]->OnMouseUp(x - this->x, y - this->y, button);
            break;
        }
}

void CompositeWidget::OnMouseMove(int oldx, int oldy, int newx, int newy)
{
    int firstchild = -1;
    for(int i = 0; i < numChildren; ++i)
        if(children[i]->ContainsCoordinate(oldx - this->x, oldy - this->y))
        {
            children[i]->OnMouseMove(oldx - this->x, oldy - this->y, newx - this->x, newy - this->y);
            firstchild = i;
            break;
        }

    for(int i = 0; i < numChildren; ++i)
        if(children[i]->ContainsCoordinate(newx - this->x, newy - this->y))
        {
            if(firstchild != i)
                children[i]->OnMouseMove(oldx - this->x, oldy - this->y, newx - this->x, newy - this->y);
            break;
        }
}


void CompositeWidget::OnKeyDown(char str)
{
    if(focussedChild != 0)
        focussedChild->OnKeyDown(str);
}

void CompositeWidget::OnKeyUp(char str)
{
    if(focussedChild != 0)
        focussedChild->OnKeyUp(str);    
}

