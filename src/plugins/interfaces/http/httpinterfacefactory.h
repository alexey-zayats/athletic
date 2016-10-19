#ifndef APPSRV_HTTPINTERFACEFACTORY
#define APPSRV_HTTPINTERFACEFACTORY

#include <appsrv/communicationinterface.h>

namespace AppSrv
{
    class HttpInterfaceFactory: public QObject, public CommunicationInterface::Factory
    {
        Q_OBJECT
        Q_INTERFACES(AppSrv::CommunicationInterface::Factory)
        public:
            virtual CommunicationInterface* createInterface(QObject* parent) const;
    };
}

#endif // APPSRV_HTTPINTERFACEFACTORY
