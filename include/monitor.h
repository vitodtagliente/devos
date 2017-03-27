
#ifndef __MONITOR_H_
#define __MONITOR_H_

#include <port.h>

class Monitor
{
    private:
        unsigned short *str_pointer;
        int color;
        unsigned char fore;
        unsigned char back;
        int x;
        int y;

        void scroll();
        void moveCursor();

    public:
        static Monitor* singleton;

        Monitor();
        void clear();
        void write(unsigned char c);
        void write(const char *text);
        void writeLine(unsigned char c);
        void writeLine(const char *text);
        void setColor(unsigned char forecolor, unsigned char backcolor);
        void setForeground(unsigned char fore);
        void setBackground(unsigned char back);
        unsigned char getForeground();
        unsigned char getBackground();

        static void printf(const char *str);

        static const unsigned char black = 0x00;
        static const unsigned char blue = 0x01;
        static const unsigned char green = 0x02;
        static const unsigned char cyan = 0x03;
        static const unsigned char red = 0x04;
        static const unsigned char magenta = 0x05;
        static const unsigned char brown = 0x06;
        static const unsigned char light_grey = 0x07;
        static const unsigned char dark_grey = 0x08;
        static const unsigned char light_blue = 0x09;
        static const unsigned char light_green = 0x0A;
        static const unsigned char light_cyan = 0x0B;
        static const unsigned char light_red = 0x0C;
        static const unsigned char light_magenta = 0x0D;
        static const unsigned char light_brown = 0x0E;
        static const unsigned char white = 0x0F;
};

#endif