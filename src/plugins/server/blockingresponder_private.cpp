#include "blockingresponder_private.h"

#include "request.h"
#include "requestrunner.h"

#include <QTimer>

namespace Server
{
    BlockingResponder::Private::Private(SpawnerBase* spawner, const char* responderSlot, QObject* parent)
    : RequestQueue(spawner, responderSlot, parent)
    {
    }

    void BlockingResponder::Private::start(RequestRunner* runner)
    {
        runner->run();
        if(runner->autoDelete())
        {
            delete runner;
        }
    }
}
