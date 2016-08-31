#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/resource.h>
#include <sys/utsname.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <assert.h>

#include "systemid.h"

namespace Utils {

SystemID::SystemID(QObject *parent) : QObject(parent)
{

}

const QString SystemID::getMachineName()
{
   static struct utsname u;

   if ( uname( &u ) < 0 )
   {
      assert(0);
      return QLatin1String("unknown");
   }

   return QLatin1String(u.nodename);
}

#ifdef Q_OS_MACX

#include <mach-o/arch.h>

unsigned short SystemID::getCpuHash()
{
    const NXArchInfo* info = NXGetLocalArchInfo();
    unsigned short val = 0;
    val += (unsigned short)info->cputype;
    val += (unsigned short)info->cpusubtype;
    return val;
}

#else // !Q_OS_MACX

void SystemID::getCpuid( unsigned int* p, unsigned int ax )
{
    __asm __volatile
    (   "movl %%ebx, %%esi\n\t"
        "cpuid\n\t"
        "xchgl %%ebx, %%esi"
        : "=a" (p[0]), "=S" (p[1]),
          "=c" (p[2]), "=d" (p[3])
        : "0" (ax)
    );
}

unsigned short SystemID::getCpuHash()
{
    unsigned int cpuinfo[4] = { 0, 0, 0, 0 };
    getCpuid( cpuinfo, 0 );
    unsigned short hash = 0;
    unsigned int* ptr = (&cpuinfo[0]);
    for ( unsigned int i = 0; i < 4; i++ )
        hash += (ptr[i] & 0xFFFF) + ( ptr[i] >> 16 );

    return hash;
}
#endif // !Q_OS_MACX


unsigned short SystemID::hashMacAddress( unsigned char* mac )
{
   unsigned short hash = 0;

   for ( unsigned int i = 0; i < 6; i++ )
   {
      hash += ( mac[i] << (( i & 1 ) * 8 ));
   }
   return hash;
}

#include <ifaddrs.h>
#include <net/if.h>

unsigned short SystemID::getMacHash()
{
    unsigned short mac = 0;

#ifdef Q_OS_MACX

    struct ifaddrs* ifaphead;
    if ( getifaddrs( &ifaphead ) != 0 )
        assert(0);

    // iterate over the net interfaces
    struct ifaddrs* ifap;
    for ( ifap = ifaphead; ifap; ifap = ifap->ifa_next ) {
        struct sockaddr* sdl = (struct sockaddr*)ifap->ifa_addr;
        if ( sdl && ( sdl->sa_family == AF_LINK ) ) {
            mac = hashMacAddress( (unsigned char*)(sdl->sa_data)); //sdl->sdl_data) + sdl->sdl_nlen) );
            break;
        }
    }

    freeifaddrs( ifaphead );

#else // !Q_OS_MACX

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP );
    if ( sock < 0 ) return;

    // enumerate all IP addresses of the system
    struct ifconf conf;
    char ifconfbuf[ 128 * sizeof(struct ifreq)  ];
    memset( ifconfbuf, 0, sizeof( ifconfbuf ));
    conf.ifc_buf = ifconfbuf;
    conf.ifc_len = sizeof( ifconfbuf );
    if ( ioctl( sock, SIOCGIFCONF, &conf ))
        assert(0);

    // get MAC address
    struct ifreq* ifr;
    for ( ifr = conf.ifc_req;
          (char*)ifr < (char*)conf.ifc_req + conf.ifc_len;
          ifr++ )
    {
        if ( ifr->ifr_addr.sa_data == (ifr+1)->ifr_addr.sa_data )
            continue;  // duplicate, skip it

        if ( ioctl( sock, SIOCGIFFLAGS, ifr ))
            continue;  // failed to get flags, skip it

        if ( ioctl( sock, SIOCGIFHWADDR, ifr ) == 0 ) {
            mac = hashMacAddress( (unsigned char*)&(ifr->ifr_addr.sa_data));
            break;
        }
    }

    close( sock );

#endif // !Q_OS_MACX

   return mac;
}

unsigned short SystemID::getVolumeHash()
{
    // we don't have a 'volume serial number' like on windows. Lets hash the system name instead.
    unsigned char* sysname = (unsigned char*)getMachineName().toLocal8Bit().data();
    unsigned short hash = 0;

    for ( unsigned int i = 0; sysname[i]; i++ )
        hash += ( sysname[i] << (( i & 1 ) * 8 ));

    return hash;
}

}
