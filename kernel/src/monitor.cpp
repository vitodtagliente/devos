
#include <monitor.h>
#include <system.h>

Monitor* Monitor::singleton = 0;

Monitor::Monitor()
{
    if( singleton == 0 )
        singleton = this;
        
    this->str_pointer = (unsigned short *)0xB8000;
    this->setColor(Monitor::white, Monitor::black);
    this->x = this->y = 0;
    this->clear();
}

/* Scrolls the Monitor */
void Monitor::scroll()
{
    unsigned blank, temp;

    /* A blank is defined as a space... we need to give it
    *  backcolor too */
    blank = 0x20 | (this->color << 8);

    /* Row 25 is the end, this means we need to scroll up */
    if(this->y >= 25)
    {
        /* Move the current str_pointer chunk that makes up the Monitor
        *  back in the buffer by a line */
        temp = this->y - 25 + 1;
        memcpy (this->str_pointer, this->str_pointer + temp * 80, (25 - temp) * 80 * 2);

        /* Finally, we set the chunk of memory that occupies
        *  the last line of str_pointer to our 'blank' character */
        memsetw (this->str_pointer + (25 - temp) * 80, blank, 80);
        this->y = 25 - 1;
    }
}


/* Updates the hardware cursor: the little blinking line
*  on the Monitor under the last character pressed! */
void Monitor::moveCursor()
{
    unsigned temp;

    /* The equation for finding the index in a linear
    *  chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    temp = this->y * 80 + this->x;

    /* This sends a command to indicies 14 and 15 in the
    *  CRT Control Register of the VGA controller. These
    *  are the high and low bytes of the index that show
    *  where the hardware cursor is to be 'blinking'. To
    *  learn more, you should look up some VGA specific
    *  programming documents. A great start to graphics:
    *  http://www.brackeen.com/home/vga */
    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

void Monitor::clear()
{
    unsigned blank;
    int i;

    /* Again, we need the 'short' that will be used to
    *  represent a space with color */
    blank = 0x20 | (this->color << 8);

    /* Sets the entire Monitor to spaces in our current
    *  color */
    for(i = 0; i < 25; i++)
        memsetw (this->str_pointer + i * 80, blank, 80);

    /* Update out virtual cursor, and then move the
    *  hardware cursor */
    this->x = 0;
    this->y = 0;
    this->moveCursor();
}

/* Puts a single character on the Monitor */
void Monitor::write(unsigned char c)
{
    unsigned short *where;
    unsigned att = this->color << 8;

    /* Handle a backspace, by moving the cursor back one space */
    if(c == 0x08)
    {
        if(this->x != 0) this->x--;
    }
    /* Handles a tab by incrementing the cursor's x, but only
    *  to a point that will make it divisible by 8 */
    else if(c == 0x09)
    {
        this->x = (this->x + 8) & ~(8 - 1);
    }
    /* Handles a 'Carriage Return', which simply brings the
    *  cursor back to the margin */
    else if(c == '\r')
    {
        this->x = 0;
    }
    /* We handle our newlines the way DOS and the BIOS do: we
    *  treat it as if a 'CR' was also there, so we bring the
    *  cursor to the margin and we increment the 'y' value */
    else if(c == '\n')
    {
        this->x = 0;
        this->y++;
    }
    /* Any character greater than and including a space, is a
    *  printable character. The equation for finding the index
    *  in a linear chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    else if(c >= ' ')
    {
        where = this->str_pointer + (this->y * 80 + this->x);
        *where = c | att;	/* Character AND attributes: color */
        this->x++;
    }

    /* If the cursor has reached the edge of the Monitor's width, we
    *  insert a new line in there */
    if(this->x >= 80)
    {
        this->x = 0;
        this->y++;
    }

    /* Scroll the Monitor if needed, and finally move the cursor */
    this->scroll();
    this->moveCursor();
}

/* Uses the above routine to output a string... */
void Monitor::write(const char *str)
{
    int i;

    for (i = 0; i < strlen(str); i++)
    {
        write(str[i]);
    }
}

void Monitor::writeLine(unsigned char c){
    this->write(c);
    this->write("\n");
}

void Monitor::writeLine(const char * str){
    this->write(str);
    this->write("\n");
}

void Monitor::setColor(unsigned char forecolor, unsigned char backcolor)
{
    this->fore = forecolor;
    this->back = backcolor;
    /* Top 4 bytes are the background, bottom 4 bytes
    *  are the foreground color */
    this->color = (backcolor << 4) | (forecolor & 0x0F);
}

void Monitor::setForeground(unsigned char foreColor)
{
    this->setColor(foreColor, this->back);
}

void Monitor::setBackground(unsigned char backColor)
{
    this->setColor(this->fore, backColor);
}

void Monitor::printf(const char* str){
    if( singleton != 0 ){
        singleton->write(str);
    }
}