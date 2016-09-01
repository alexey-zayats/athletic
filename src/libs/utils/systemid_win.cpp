
#include <windows.h>
#include <intrin.h>
#include <iphlpapi.h>

#include "systemid_p.h"

namespace Utils {

const QString SystemIdPrivate::getMachineName()
{
   TCHAR computerName[1024];
   DWORD size = 1024;
   GetComputerName( computerName, &size );
   return QLatin1String( (const char*)(computerName[0]) );
}

inline unsigned short hashMacAddress( PIP_ADAPTER_INFO info )
{
   unsigned short hash = 0;
   for ( unsigned int i = 0; i < info->AddressLength; i++ )
   {
      hash += ( info->Address[i] << (( i & 1 ) * 8 ));
   }
   return hash;
}

unsigned short SystemIdPrivate::getMacHash()
{
   IP_ADAPTER_INFO AdapterInfo[32];
    DWORD dwBufLen = sizeof( AdapterInfo );

    DWORD dwStatus = GetAdaptersInfo( AdapterInfo, &dwBufLen );
    if ( dwStatus != ERROR_SUCCESS )
        return 0; // no adapters.

    PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
    return hashMacAddress( pAdapterInfo );
}

unsigned short SystemIdPrivate::getVolumeHash()
{
   DWORD serialNum = 0;

   // Determine if this volume uses an NTFS file system.
   GetVolumeInformation( TEXT("C:\\"), NULL, 0, &serialNum, NULL, NULL, NULL, 0 );

   return (unsigned short)(( serialNum + ( serialNum >> 16 )) & 0xFFFF );
}

unsigned short SystemIdPrivate::getCpuHash()
{
   int cpuinfo[4] = { 0, 0, 0, 0 };
   __cpuid( cpuinfo, 0 );
   unsigned short hash = 0;
   unsigned short* ptr = (unsigned short*)(&cpuinfo[0]);
   for ( int i = 0; i < 8; i++ )
      hash += ptr[i];

   return hash;
}

}
