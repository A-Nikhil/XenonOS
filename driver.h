#ifndef __DRIVER_H
#define __DRIVER_H

	class Driver
	{
	public:
		Driver();
		~Driver();
		
		virtual void Activate();
		virtual int Reset(); //Bootloader might have things left in an uncertain state
		virtual void Deactivate();
		
	};

	class DriverManager
	{
		private:
			Driver* drivers[265]; //Fixed size, because we havent done memory management yet
			int numDrivers;
		public:
			DriverManager();
			void AddDriver(Driver*);
			void ActivateAll();
	};


#endif
	
