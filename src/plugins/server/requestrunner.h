#ifndef REQUESTRUNNER_H
#define REQUESTRUNNER_H

#include "threadedresponder.h"

#include <QRunnable>

namespace Server
{
    /**@internal Class to run a Request.
     *
     * @see ThreadedResponder
     */
    class RequestRunner : public QRunnable
    {
        public:
            RequestRunner(SpawnerBase* spawner, const char* responderSlot, Request* request);
            ~RequestRunner();
            void run();
            Request* request() const;
        private:
            SpawnerBase* m_spawner;
            const char* m_slot;
            Request* m_request;
    };
};
#endif // REQUESTRUNNER_H
