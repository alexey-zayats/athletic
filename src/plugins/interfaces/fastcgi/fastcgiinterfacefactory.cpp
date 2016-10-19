#include "fastcgiinterfacefactory.h"
#include "fastcgiinterface.h"

namespace FastCgi
{
    CommunicationInterface* AppSrvInterfaceFactory::createInterface(QObject* parent) const
    {
        return new AppSrvInterface(parent);
    }
}

