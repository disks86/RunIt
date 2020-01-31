#ifndef RUNIT_OPTIONALHEADERDATADIRECTORIES_H
#define RUNIT_OPTIONALHEADERDATADIRECTORIES_H

#include <cstdint>

struct HeaderDataDirectory
{
    uint32_t VirtualAddress;
    uint32_t Size;
};

struct OptionalHeaderDataDirectories
{
    HeaderDataDirectory ExportTable;
    HeaderDataDirectory ImportTable;
    HeaderDataDirectory ResourceTable;
    HeaderDataDirectory ExceptionTable;
    HeaderDataDirectory CertificateTable;
    HeaderDataDirectory BaseRelocationTable;
    HeaderDataDirectory Debug;
    HeaderDataDirectory Architecture;
    HeaderDataDirectory GlobalPointer;
    HeaderDataDirectory TlsTable;
    HeaderDataDirectory LoadConfigTable;
    HeaderDataDirectory BoundImport;
    HeaderDataDirectory Iat;
    HeaderDataDirectory DelayImportDescriptor;
    HeaderDataDirectory ClrRuntimeHeader;
    HeaderDataDirectory Reserved;
};

#endif //RUNIT_OPTIONALHEADERDATADIRECTORIES_H
