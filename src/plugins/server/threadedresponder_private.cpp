#include "threadedresponder_private.h"

#include "request.h"
#include "requestrunner.h"
#include "threadpool.h"

#include <QTimer>

namespace Server
{
    ThreadedResponder::Private::Private(SpawnerBase* spawner, const char* responderSlot, QObject* parent)
    : RequestQueue(spawner, responderSlot, parent)
    , m_threadPool(new ThreadPool(this))
    {
    }

    void ThreadedResponder::Private::start(RequestRunner* runner)
    {
        m_threadPool->start(runner, runner->request());
    }
}
