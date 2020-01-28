#include "Executable.h"

const int MS_DOS_SIGNATURE_OFFSET = 0x3c;
const int PE32 = 0x10b;
const int PE32_PLUS = 0x20b;

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
    std::cout << "--- COFF File Header ---" << std::endl;
    mInputFile.read ((char*)&mCOFFHeader, sizeof(COFFHeader));
    std::cout << "Machine: " << mCOFFHeader.Machine << std::endl;
    std::cout << "NumberOfSections: " << mCOFFHeader.NumberOfSections << std::endl;
    std::cout << "TimeDateStamp: " << mCOFFHeader.TimeDateStamp << std::endl;
    std::cout << "PointerToSymbolTable: " << mCOFFHeader.PointerToSymbolTable << std::endl;
    std::cout << "NumberOfSymbols: " << mCOFFHeader.NumberOfSymbols << std::endl;
    std::cout << "SizeOfOptionalHeader: " << mCOFFHeader.SizeOfOptionalHeader << std::endl;
    std::cout << "Characteristics: " << mCOFFHeader.Characteristics << std::endl;

    //Optional Header Standard Fields
    std::cout << "--- Optional Header Standard Fields  ---" << std::endl;
    mInputFile.read ((char*)&mOptionalHeaderStandardFields, sizeof(OptionalHeaderStandardFields)-4);
    if(mOptionalHeaderStandardFields.Magic == PE32)
    {
        mInputFile.read ((char*)&mOptionalHeaderStandardFields.BaseOfData, 4);
    }
    std::cout << "Magic: " << mOptionalHeaderStandardFields.Magic << std::endl;
    std::cout << "MajorLinkerVersion: " << (uint32_t)mOptionalHeaderStandardFields.MajorLinkerVersion << std::endl;
    std::cout << "MinorLinkerVersion: " << (uint32_t)mOptionalHeaderStandardFields.MinorLinkerVersion << std::endl;
    std::cout << "SizeOfCode: " << mOptionalHeaderStandardFields.SizeOfCode << std::endl;
    std::cout << "SizeOfInitializedData: " << mOptionalHeaderStandardFields.SizeOfInitializedData << std::endl;
    std::cout << "SizeOfUninitializedData: " << mOptionalHeaderStandardFields.SizeOfUninitializedData << std::endl;
    std::cout << "AddressOfEntryPoint: " << mOptionalHeaderStandardFields.AddressOfEntryPoint << std::endl;
    std::cout << "BaseOfCode: " << mOptionalHeaderStandardFields.BaseOfCode << std::endl;
    if(mOptionalHeaderStandardFields.Magic == PE32)
    {
        std::cout << "BaseOfData: " << mOptionalHeaderStandardFields.BaseOfData << std::endl;
    }

    //Optional Header Windows-Specific Fields

}

void Executable::LoadElf()
{
    std::cout << "ELF not supported!" << std::endl;
    abort();
}
