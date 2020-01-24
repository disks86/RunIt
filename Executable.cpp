#include "Executable.h"

const int MS_DOS_SIGNATURE_OFFSET = 0x3c;

Executable::Executable(std::string& filename)
{
    std::cout << "Opening: " << filename << std::endl;
    mInputFile.open(filename,std::ios::in | std::ios::binary);

    if(filename.ends_with("exe") || filename.ends_with("EXE"))
    {
        LoadPE();
    }
    else
    {
        LoadElf();
    }
}

void Executable::LoadPE()
{

    //MS-DOS Stub
    mInputFile.seekg (MS_DOS_SIGNATURE_OFFSET);
    mInputFile.read ((char*)&mPESignatureOffset,4);
    std::cout << "Signature Offset: " << mPESignatureOffset << std::endl;

    //Signature
    mInputFile.seekg (mPESignatureOffset);
    mInputFile.read (mPESignature, 4);
    std::cout << "Signature: " << mPESignature << std::endl;

    //COFF File Header
    mInputFile.read ((char*)&mCOFFHeader, sizeof(COFFHeader));
    std::cout << "Machine: " << mCOFFHeader.Machine << std::endl;
    std::cout << "NumberOfSections: " << mCOFFHeader.NumberOfSections << std::endl;
    std::cout << "TimeDateStamp: " << mCOFFHeader.TimeDateStamp << std::endl;
    std::cout << "PointerToSymbolTable: " << mCOFFHeader.PointerToSymbolTable << std::endl;
    std::cout << "NumberOfSymbols: " << mCOFFHeader.NumberOfSymbols << std::endl;
    std::cout << "SizeOfOptionalHeader: " << mCOFFHeader.SizeOfOptionalHeader << std::endl;
    std::cout << "Characteristics: " << mCOFFHeader.Characteristics << std::endl;

}

void Executable::LoadElf()
{
    std::cout << "ELF not supported!" << std::endl;
    abort();
}
