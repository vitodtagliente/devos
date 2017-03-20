 
#ifndef __DRIVER_H
#define __DRIVER_H

class Driver
{
    public:
        Driver();
        ~Driver();
        
        virtual void Enable();
        virtual int Reset();
        virtual void Disable();
};

class DriverManager
{
    public:
        Driver* drivers[255];
        int numDrivers;
        
    public:
        DriverManager();
        void Add(Driver*);
        
        void EnableAll();    
};
    
#endif