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



#endif
	
