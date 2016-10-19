#include "blockingresponder.h"
#include "blockingresponder_private.h"

namespace Server
{
    BlockingResponder::BlockingResponder(SpawnerBase* spawner, const char* responderSlot, QObject* parent)
    : AbstractResponder(parent)
    , d(new Private(spawner, responderSlot, this))
    {
    }

    BlockingResponder::~BlockingResponder()
    {
    }

    void BlockingResponder::respond(Request* request)
    {
        d->respond(request);
    }

    void BlockingResponder::respond(SpawnerBase* spawner, const char* responderSlot, Request* request)
    {
        d->respond(spawner, responderSlot, request);
    }
};
