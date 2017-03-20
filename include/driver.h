 
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
        Driver* drivers[265];
        int numDrivers;
        
    public:
        DriverManager();
        void AddDriver(Driver*);
        
        void EnableAll();    
};
    
#endif