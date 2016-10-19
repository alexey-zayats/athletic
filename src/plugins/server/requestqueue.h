#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include "abstractresponder.h"

#include <QQueue>

class QTimer;

namespace Server
{
    class RequestRunner;
    class RequestQueue : public QObject
    {
        Q_OBJECT
        public:
            RequestQueue(SpawnerBase* spawner, const char* responderSlot, QObject* parent);
            void respond(Request*);
            void respond(SpawnerBase* spawner, const char* responderSlot, Request* request);
        protected:
            virtual void start(RequestRunner* runner) = 0;
        private slots:
            void flushQueue();
        private:
            SpawnerBase* m_spawner;
            const char* m_responderSlot;

            QTimer* m_queueRunner;

            QQueue<RequestRunner*> m_unhandledRequests;
    };
};
#endif // REQUESTQUEUE_H
