//
// Created by cschaefer on 1/22/20.
//

#ifndef RUNIT_EXECUTABLE_H
#define RUNIT_EXECUTABLE_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "COFFHeader.h"

class Executable
{
private:
    std::ifstream mInputFile;

    //PE
    long mPESignatureOffset=0;
    char mPESignature[5]={};//Add extra character so we'll always have a null terminator.
    COFFHeader mCOFFHeader={};

    //ELF



public:
    Executable(std::string& filename);
    void LoadPE();
    void LoadElf();
};


#endif //RUNIT_EXECUTABLE_H
