#ifndef REQUESTFACTORY_H
#define REQUESTFACTORY_H

#include "clientiodevice.h"
#include "request.h"

namespace Server
{
    class RequestFactory : public Request
    {
        public:
            static Request* createRequest(ClientIODevice*, ClientIODevice::HeaderMap extraHeaders, QObject* parent);
    };
};
#endif // REQUESTFACTORY_H
