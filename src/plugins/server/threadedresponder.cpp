#include "threadedresponder.h"
#include "threadedresponder_private.h"

namespace Server
{
    ThreadedResponder::ThreadedResponder(SpawnerBase* spawner, const char* responderSlot, QObject* parent)
    : AbstractResponder(parent)
    , d(new Private(spawner, responderSlot, this))
    {
    }

    ThreadedResponder::~ThreadedResponder()
    {
    }

    void ThreadedResponder::respond(Server::Request* request)
    {
        d->respond(request);
    }

    void ThreadedResponder::respond(SpawnerBase* spawner, const char* responderSlot, Request* request)
    {
        d->respond(spawner, responderSlot, request);
    }
};
