#ifndef __XENONOS__HARDWARECOMMUNICATION____PORT_H
#define __XENONOS__HARDWARECOMMUNICATION____PORT_H

#include "types.h"

namespace xenonos {
	namespace hardwarecommunication {
		class Port {
			protected:
				xenonos::common::uint16_t portnumber;
				Port(xenonos::common::uint16_t portnumber);
				~Port();
		};

		// For 8 Bit Data
		class Port8Bit : public Port {
			public:
				Port8Bit(xenonos::common::uint16_t portnumber);
				~Port8Bit();
				virtual void Write(xenonos::common::uint8_t data);
				virtual xenonos::common::uint8_t Read();
		};

		// For 8 Bit data ports which are slightly slow
		class Port8BitSlow : public Port8Bit {
			public:
				Port8BitSlow(xenonos::common::uint16_t portnumber);
				~Port8BitSlow();
				virtual void Write(xenonos::common::uint8_t data);
		};

		// For 16 Bit Data
		class Port16Bit : public Port {
			public:
				Port16Bit(xenonos::common::uint16_t portnumber);
				~Port16Bit();
				virtual void Write(xenonos::common::uint16_t data);
				virtual xenonos::common::uint16_t Read();
		};

		// For 32 Bit Data
		class Port32Bit : public Port {
			public:
				Port32Bit(xenonos::common::uint16_t portnumber);
				~Port32Bit();
				virtual void Write(xenonos::common::uint32_t data);
				virtual xenonos::common::uint32_t Read();
		};
	}
}

#endif