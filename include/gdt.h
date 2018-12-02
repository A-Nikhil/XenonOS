
#ifndef __XENONOS__GDT_H
#define __XENONOS__GDT_H

#include <common/types.h>

namespace xenonos {
    class GlobalDescriptorTable {
        public:
            class SegmentDescriptor {
                private:
                    xenonos::common::uint16_t limit_lo;
                    xenonos::common::uint16_t base_lo;
                    xenonos::common::uint8_t base_hi;
                    xenonos::common::uint8_t type;
                    xenonos::common::uint8_t flag_limit_hi;
                    xenonos::common::uint8_t base_vhi;
                public:
                    SegmentDescriptor(xenonos::common::uint32_t base, xenonos::common::uint32_t limit, xenonos::common::uint8_t type);
                    xenonos::common::uint32_t Base();
                    xenonos::common::uint32_t Limit();
            } __attribute__((packed));
            
        SegmentDescriptor nullSegmentSelector;
        SegmentDescriptor unusedSegmentSelector;
        SegmentDescriptor codeSegmentSelector;
        SegmentDescriptor dataSegmentSelector;
        
        public:
            GlobalDescriptorTable();
            ~GlobalDescriptorTable();
            
            xenonos::common::uint16_t CodeSegmentSelector();
            xenonos::common::uint16_t DataSegmentSelector();
    };
}

#endif
