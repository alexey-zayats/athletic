#ifndef BLOCKINGRESPONDER_PRIVATE_H
#define BLOCKINGRESPONDER_PRIVATE_H

#include "blockingresponder.h"
#include "requestqueue.h"

#include <QQueue>

namespace Server
{
    class BlockingResponder::Private : public RequestQueue
    {
        Q_OBJECT
        public:
            Private(SpawnerBase* spawner, const char* responderSlot, QObject* parent);
        protected:
            void start(RequestRunner* runner);
    };
};
#endif // BLOCKINGRESPONDER_PRIVATE_H
