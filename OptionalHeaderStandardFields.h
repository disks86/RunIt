#ifndef RUNIT_OPTIONALHEADERSTANDARDFIELDS_H
#define RUNIT_OPTIONALHEADERSTANDARDFIELDS_H

#include <cstdint>

struct OptionalHeaderStandardFields
{
    uint16_t Magic;
    uint8_t MajorLinkerVersion;
    uint8_t MinorLinkerVersion;
    uint32_t SizeOfCode;
    uint32_t SizeOfInitializedData;
    uint32_t SizeOfUninitializedData;
    uint32_t AddressOfEntryPoint;
    uint32_t BaseOfCode;
    //PE32 only
    uint32_t BaseOfData;
};

#endif //RUNIT_OPTIONALHEADERSTANDARDFIELDS_H
