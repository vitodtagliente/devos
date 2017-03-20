
#include <driver.h>
 
Driver::Driver()
{
}

Driver::~Driver()
{
    
}
        
void Driver::Enable()
{

}

int Driver::Reset()
{
    return 0;
}

void Driver::Disable()
{

}

DriverManager::DriverManager()
{
    numDrivers = 0;
}

void DriverManager::Add(Driver* drv)
{
    drivers[numDrivers] = drv;
    numDrivers++;
}

void DriverManager::EnableAll()
{
    for(int i = 0; i < numDrivers; i++)
        drivers[i]->Enable();
}
