#include "driver.h"

Driver::Driver()
{
}

Driver::~Driver()
{
}
void Driver::Activate()
{
}
int Driver::Reset()
{
	return 0;
}

void Driver::Deactivate()
{
}

Drivermanager::DriverManager()
{
	numDrivers = 0;
}

void AddDriver(Driver*)
{
	drivers[numDrivers] = drv;
	numDrivers++;
}	

void Drivermanager::ActivateAll(){
	for(int i =0;i<numDrivers;i++)
		drivers[i]->Activate();	

}



#endif
	
