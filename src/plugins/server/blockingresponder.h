#ifndef BLOCKINGRESPONDER_H
#define BLOCKINGRESPONDER_H

#include "abstractresponder.h"

namespace Server
{
    /** Single-threaded dispatcher for Server requests.
     *
     * @section advantages_direct Advantages over using Manager::newRequest directly
     *  - Dealing with state within each request is easier (a new object is created for each request)
     *  - It's easy to swap for a ThreadedResponder
     *
     * @section disadvantages_direct Disadvantages over using Manager::newRequest directly
     *  - Added overhead of creating and destroying a QObject for each request
     *
     *  @see ThreadedResponder for comparison.
     */
    class BlockingResponder : public AbstractResponder
    {
        Q_OBJECT
        public:
            BlockingResponder(SpawnerBase* spawner, const char* responderSlot, QObject* parent = 0);
            ~BlockingResponder();

            void respond(SpawnerBase* spawner, const char* responderSlot, Server::Request*);
        public slots:
            void respond(Server::Request*);
        private:
            class Private;
            Private* d;
    };
};
#endif // BLOCKINGRESPONDER_H
