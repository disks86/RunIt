//
// Created by cschaefer on 1/22/20.
//

#ifndef RUNIT_EXECUTABLE_H
#define RUNIT_EXECUTABLE_H

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <variant>
#include <chrono>
#include <ctime>

#include "COFFHeader.h"
#include "OptionalHeaderStandardFields.h"
#include "OptionalHeaderWindowsSpecificFields.h"
#include "OptionalHeaderDataDirectories.h"
#include "SectionHeader.h"
#include "CodeAllocator.h"

class Executable
{
private:
    std::ifstream mInputFile;
    std::vector<char> mBuffer;
    std::map<uint64_t,std::vector<char,CodeAllocator<char>>> mCodeBlocks;

    //PE
    long mPESignatureOffset=0;
    char mPESignature[5]={};//Add extra character so we'll always have a null terminator.
    COFFHeader mCOFFHeader={};
    OptionalHeaderStandardFields mOptionalHeaderStandardFields={};
    PE32OptionalHeaderWindowsSpecificFields mPE32OptionalHeaderWindowsSpecificFields={};
    PE32PlusOptionalHeaderWindowsSpecificFields mPE32PlusOptionalHeaderWindowsSpecificFields={};
    OptionalHeaderDataDirectories mOptionalHeaderDataDirectories={};
    std::vector<SectionHeader> mSectionHeaders;

    //ELF



public:
    Executable(std::string& filename);
    void LoadPE();
    void LoadElf();
    void StartReadingTokens(char* entryPoint);
};


#endif //RUNIT_EXECUTABLE_H
