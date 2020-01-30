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

    //TODO: correct timestamp logic.
    time_t time = mCOFFHeader.TimeDateStamp;
    auto timeDateStamp = localtime(reinterpret_cast<const time_t *>(&time));

    std::cout << "--- COFF File Header ---" << std::endl;
    mInputFile.read ((char*)&mCOFFHeader, sizeof(COFFHeader));
    std::cout << "Machine: " << ToString(mCOFFHeader.Machine) << std::endl;
    std::cout << "NumberOfSections: " << mCOFFHeader.NumberOfSections << std::endl;
    std::cout << "TimeDateStamp: " << asctime(timeDateStamp) << std::endl;
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
    std::cout << "--- Optional Header Windows-Specific Fields  ---" << std::endl;
    if(mOptionalHeaderStandardFields.Magic == PE32)
    {
        mInputFile.read ((char*)&mPE32OptionalHeaderWindowsSpecificFields, sizeof(PE32OptionalHeaderWindowsSpecificFields));

        std::cout << "ImageBase: " << mPE32OptionalHeaderWindowsSpecificFields.ImageBase << std::endl;
        std::cout << "SectionAlignment: " << mPE32OptionalHeaderWindowsSpecificFields.SectionAlignment << std::endl;
        std::cout << "FileAlignment: " << mPE32OptionalHeaderWindowsSpecificFields.FileAlignment << std::endl;
        std::cout << "MajorOperatingSystemVersion: " << mPE32OptionalHeaderWindowsSpecificFields.MajorOperatingSystemVersion << std::endl;
        std::cout << "MinorOperatingSystemVersion: " << mPE32OptionalHeaderWindowsSpecificFields.MinorOperatingSystemVersion << std::endl;
        std::cout << "MajorImageVersion: " << mPE32OptionalHeaderWindowsSpecificFields.MajorImageVersion << std::endl;
        std::cout << "MinorImageVersion: " << mPE32OptionalHeaderWindowsSpecificFields.MinorImageVersion << std::endl;
        std::cout << "MajorSubsystemVersion: " << mPE32OptionalHeaderWindowsSpecificFields.MajorSubsystemVersion << std::endl;
        std::cout << "MinorSubsystemVersion: " << mPE32OptionalHeaderWindowsSpecificFields.MinorSubsystemVersion << std::endl;
        std::cout << "Win32VersionValue: " << mPE32OptionalHeaderWindowsSpecificFields.Win32VersionValue << std::endl;
        std::cout << "SizeOfImage: " << mPE32OptionalHeaderWindowsSpecificFields.SizeOfImage << std::endl;
        std::cout << "SizeOfHeaders: " << mPE32OptionalHeaderWindowsSpecificFields.SizeOfHeaders << std::endl;
        std::cout << "CheckSum: " << mPE32OptionalHeaderWindowsSpecificFields.CheckSum << std::endl;
        std::cout << "Subsystem: " << ToString(mPE32OptionalHeaderWindowsSpecificFields.Subsystem) << std::endl;
        std::cout << "DllCharacteristics: " << mPE32OptionalHeaderWindowsSpecificFields.DllCharacteristics << std::endl;
        std::cout << "SizeOfStackReserve: " << mPE32OptionalHeaderWindowsSpecificFields.SizeOfStackReserve << std::endl;
        std::cout << "SizeOfStackCommit: " << mPE32OptionalHeaderWindowsSpecificFields.SizeOfStackCommit << std::endl;
        std::cout << "SizeOfHeapReserve: " << mPE32OptionalHeaderWindowsSpecificFields.SizeOfHeapReserve << std::endl;
        std::cout << "SizeOfHeapCommit: " << mPE32OptionalHeaderWindowsSpecificFields.SizeOfHeapCommit << std::endl;
        std::cout << "LoaderFlags: " << mPE32OptionalHeaderWindowsSpecificFields.LoaderFlags << std::endl;
        std::cout << "NumberOfRvaAndSizes: " << mPE32OptionalHeaderWindowsSpecificFields.NumberOfRvaAndSizes << std::endl;
    }
    else
    {
        mInputFile.read ((char*)&mPE32PlusOptionalHeaderWindowsSpecificFields, sizeof(PE32PlusOptionalHeaderWindowsSpecificFields));

        std::cout << "ImageBase: " << mPE32PlusOptionalHeaderWindowsSpecificFields.ImageBase << std::endl;
        std::cout << "SectionAlignment: " << mPE32PlusOptionalHeaderWindowsSpecificFields.SectionAlignment << std::endl;
        std::cout << "FileAlignment: " << mPE32PlusOptionalHeaderWindowsSpecificFields.FileAlignment << std::endl;
        std::cout << "MajorOperatingSystemVersion: " << mPE32PlusOptionalHeaderWindowsSpecificFields.MajorOperatingSystemVersion << std::endl;
        std::cout << "MinorOperatingSystemVersion: " << mPE32PlusOptionalHeaderWindowsSpecificFields.MinorOperatingSystemVersion << std::endl;
        std::cout << "MajorImageVersion: " << mPE32PlusOptionalHeaderWindowsSpecificFields.MajorImageVersion << std::endl;
        std::cout << "MinorImageVersion: " << mPE32PlusOptionalHeaderWindowsSpecificFields.MinorImageVersion << std::endl;
        std::cout << "MajorSubsystemVersion: " << mPE32PlusOptionalHeaderWindowsSpecificFields.MajorSubsystemVersion << std::endl;
        std::cout << "MinorSubsystemVersion: " << mPE32PlusOptionalHeaderWindowsSpecificFields.MinorSubsystemVersion << std::endl;
        std::cout << "Win32VersionValue: " << mPE32PlusOptionalHeaderWindowsSpecificFields.Win32VersionValue << std::endl;
        std::cout << "SizeOfImage: " << mPE32PlusOptionalHeaderWindowsSpecificFields.SizeOfImage << std::endl;
        std::cout << "SizeOfHeaders: " << mPE32PlusOptionalHeaderWindowsSpecificFields.SizeOfHeaders << std::endl;
        std::cout << "CheckSum: " << mPE32PlusOptionalHeaderWindowsSpecificFields.CheckSum << std::endl;
        std::cout << "Subsystem: " << ToString(mPE32PlusOptionalHeaderWindowsSpecificFields.Subsystem) << std::endl;
        std::cout << "DllCharacteristics: " << mPE32PlusOptionalHeaderWindowsSpecificFields.DllCharacteristics << std::endl;
        std::cout << "SizeOfStackReserve: " << mPE32PlusOptionalHeaderWindowsSpecificFields.SizeOfStackReserve << std::endl;
        std::cout << "SizeOfStackCommit: " << mPE32PlusOptionalHeaderWindowsSpecificFields.SizeOfStackCommit << std::endl;
        std::cout << "SizeOfHeapReserve: " << mPE32PlusOptionalHeaderWindowsSpecificFields.SizeOfHeapReserve << std::endl;
        std::cout << "SizeOfHeapCommit: " << mPE32PlusOptionalHeaderWindowsSpecificFields.SizeOfHeapCommit << std::endl;
        std::cout << "LoaderFlags: " << mPE32PlusOptionalHeaderWindowsSpecificFields.LoaderFlags << std::endl;
        std::cout << "NumberOfRvaAndSizes: " << mPE32PlusOptionalHeaderWindowsSpecificFields.NumberOfRvaAndSizes << std::endl;
    }
}

void Executable::LoadElf()
{
    std::cout << "ELF not supported!" << std::endl;
    abort();
}
