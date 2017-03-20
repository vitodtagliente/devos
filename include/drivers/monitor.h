
#ifndef __MONITOR_H_
#define __MONITOR_H_

class Monitor
{
    private:
        unsigned short * text;
        int color;
        int x;
        int y;

        void scroll();
        void moveCursor();

    public:
        static Monitor* singleton;

        Monitor();
        void clear();
        void putch(unsigned char c);
        void puts(const char *str);
        void setColor(unsigned char forecolor, unsigned char backcolor);

        static void printf(const char *str);
};

#endif