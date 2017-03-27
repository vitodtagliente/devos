#ifndef __LOG_H
#define __LOG_H

#include <monitor.h>

class Log
{
    public:
        static void log(const char* str);
        static void log(const char* str, unsigned char color);
        static void error(const char* str);
        static void warning(const char* str);
        static void info(const char* str);
        static void success(const char* str);
};

#endif