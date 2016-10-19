#include "scgiinterfacefactory.h"
#include "scgiinterface.h"

namespace AppSrv
{
    CommunicationInterface* ScgiInterfaceFactory::createInterface(QObject* parent) const
    {
        return new ScgiInterface(parent);
    }
}
