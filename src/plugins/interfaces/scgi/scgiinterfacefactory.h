#ifndef APPSRV_SCGIINTERFACEFACTORY
#define APPSRV_SCGIINTERFACEFACTORY

#include <appsrv/communicationinterface.h>

namespace AppSrv
{
    class ScgiInterfaceFactory: public QObject, public CommunicationInterface::Factory
    {
        Q_OBJECT
        Q_INTERFACES(AppSrv::CommunicationInterface::Factory)
        public:
            virtual CommunicationInterface* createInterface(QObject* parent) const;
    };
}

#endif // APPSRV_SCGIINTERFACEFACTORY
