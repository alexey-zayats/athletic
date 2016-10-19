#ifndef THREADEDRESPONDER_PRIVATE_H
#define THREADEDRESPONDER_PRIVATE_H

#include "requestqueue.h"
#include "threadedresponder.h"

namespace Server
{
    class ThreadPool;
    class ThreadedResponder::Private : public RequestQueue
    {
        Q_OBJECT
        public:
            Private(SpawnerBase* spawner, const char* responderSlot, QObject* parent);
        protected:
            void start(RequestRunner* runner);
        private:
            ThreadPool* m_threadPool;
    };
};
#endif // THREADEDRESPONDER_PRIVATE_H
