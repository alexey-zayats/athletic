#ifndef COMMUNICATIONINTERFACE_WORKER_H
#define COMMUNICATIONINTERFACE_WORKER_H

#include "clientiodevice.h"
#include "communicationinterface.h"

#include <QObject>

namespace Server
{
    class CommunicationInterface::Worker : public QObject
    {
        Q_OBJECT
        signals:
            /** This worker is done.
             *
             * @param inThread is the thread that this worker
             * 	is running in.
             */
            void finished(QThread* inThread);
            void newRequest(ClientIODevice* device);
        protected:
            Worker(QObject* parent);
    };
}

#endif // COMMUNICATIONINTERFACE_WORKER_H
