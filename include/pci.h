#ifndef __PCI_H
#define __PCI_H

#include <port.h>

class PCI
{
        Port32Bit dataPort;
        Port32Bit commandPort;
        
    public:
        PCI();
        ~PCI();
        
        unsigned int Read(unsigned short bus, unsigned short device, unsigned short function, unsigned int registeroffset);
        void Write(unsigned short bus, unsigned short device, unsigned short function, unsigned int registeroffset, unsigned int value);
        /*
        bool DeviceHasFunctions(unsigned short bus, unsigned short device);
        
        void SelectDrivers(drivers::DriverManager* driverManager, hardwarecommunication::InterruptManager* interrupts);
        drivers::Driver* GetDriver(PeripheralComponentInterconnectDeviceDescriptor dev, hardwarecommunication::InterruptManager* interrupts);
        PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(unsigned short bus, unsigned short device, unsigned short function);
        BaseAddressRegister GetBaseAddressRegister(unsigned short bus, unsigned short device, unsigned short function, unsigned short bar);
        */
};

#endif