#ifndef THREADEDRESPONDER_H
#define THREADEDRESPONDER_H

#include "abstractresponder.h"

namespace Server
{
    /** Multithreaded dispatcher for Server requests.
     *
     * @see BlockingResponder for advantages/disadvantages over using Manager::newRequest directly
     *
     * @section advantages_blocking Advantages over using BlockingResponder
     *  - In some cases, may be faster
     *
     * @section disadvantages_blocking Disadvantages over using BlockingResponder
     *  - In many cases, will be slow due to threading overhead
     *  - Your code must be thread-safe
     */
    class ThreadedResponder : public AbstractResponder
    {
        Q_OBJECT
        public:
            ThreadedResponder(SpawnerBase* spawner, const char* responderSlot, QObject* parent = 0);
            ~ThreadedResponder();

            void respond(SpawnerBase* spawner, const char* responderSlot, Server::Request*);
        public slots:
            void respond(Server::Request*);
        private:
            class Private;
            Private* d;
    };
};
#endif // THREADEDRESPONDER_H
