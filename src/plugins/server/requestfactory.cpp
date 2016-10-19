#include "requestfactory.h"

#include "request_private.h"

namespace Server
{
    Request* RequestFactory::createRequest(ClientIODevice* device, ClientIODevice::HeaderMap extraHeaders, QObject* parent)
    {
        Request::Private* d = new Request::Private(device);
        d->serverData.unite(extraHeaders);
        return new Request(d, parent);
    }
};
