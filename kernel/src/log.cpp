#include <log.h>

void Log::log(const char* str)
{
    Monitor *m;
    if(Monitor::singleton != 0)
        m = Monitor::singleton;
    else 
    {
        Monitor monitor;
        m = &monitor;
    }

    m->writeLine(str);
}


void Log::log(const char* str, unsigned char color)
{
    Monitor *m;
    if(Monitor::singleton != 0)
        m = Monitor::singleton;
    else 
    {
        Monitor monitor;
        m = &monitor;
    }

    unsigned char last_color = m->getForeground();
    m->setForeground(color);
    m->writeLine(str);
    m->setForeground(last_color);
}

void Log::info(const char* str)
{
    log(str, Monitor::light_cyan);
}

void Log::success(const char* str)
{
    log(str, Monitor::light_green);
}

void Log::warning(const char* str)
{
    log(str, Monitor::light_magenta);
}

void Log::error(const char* str)
{
    log(str, Monitor::light_red);
}