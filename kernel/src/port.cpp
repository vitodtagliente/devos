
#include <port.h>

/* We will use this later on for reading from the I/O ports to get data
*  from devices such as the keyboard. We are using what is called
*  'inline assembly' in these routines to actually do the work */
unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

/* We will use this to write to I/O ports to send bytes to devices. This
*  will be used in the next tutorial for changing the textmode cursor
*  position. Again, we use some inline assembly for the stuff that simply
*  cannot be done in C */
void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

Port::Port(unsigned short portnumber)
{
    this->portnumber = portnumber;
}

Port::~Port()
{
}





Port8Bit::Port8Bit(unsigned short portnumber)
    : Port(portnumber)
{
}

Port8Bit::~Port8Bit()
{
}

void Port8Bit::Write(unsigned char data)
{
    Write8(portnumber, data);
}

unsigned char Port8Bit::Read()
{
    return Read8(portnumber);
}





Port8BitSlow::Port8BitSlow(unsigned short portnumber)
    : Port8Bit(portnumber)
{
}

Port8BitSlow::~Port8BitSlow()
{
}

void Port8BitSlow::Write(unsigned char data)
{
    Write8Slow(portnumber, data);
}





Port16Bit::Port16Bit(unsigned short portnumber)
    : Port(portnumber)
{
}

Port16Bit::~Port16Bit()
{
}

void Port16Bit::Write(unsigned short data)
{
    Write16(portnumber, data);
}

unsigned short Port16Bit::Read()
{
    return Read16(portnumber);
}





Port32Bit::Port32Bit(unsigned short portnumber)
    : Port(portnumber)
{
}

Port32Bit::~Port32Bit()
{
}

void Port32Bit::Write(unsigned int data)
{
    Write32(portnumber, data);
}

unsigned int Port32Bit::Read()
{
    return Read32(portnumber);
}

