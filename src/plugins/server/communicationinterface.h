#ifndef COMMUNICATIONINTERFACE_H
#define COMMUNICATIONINTERFACE_H

#include "clientiodevice.h"
#include "server_global.h"

#include <QtPlugin>

#include <QObject>
#include <QStringList>

class QThread;

namespace Server
{
    class Request;
    /** @internal Abstract interface for recieving requests from the HTTPD.
     *
     * This might be modified once multiple interfaces are supported,
     * and it becomes more apparent what code can be shared.
     *
     * @ingroup plugins
     */
    class SERVER_EXPORT CommunicationInterface : public QObject
    {
        Q_OBJECT
        public:
            /// Worker job that can be put in a separate thread
            class Worker;

            virtual ~CommunicationInterface();
            virtual bool isFinished() const = 0;
            virtual QStringList backends() const = 0;
            /** Backends that appear to be appropriate, given the environment.
             *
             * For example, FCGI can be started iff the FCGI socket is open
             * appropriately.
             *
             * This must only return backends where there is evidence that a given
             * backend is wanted, based on the environment.
             */
            virtual QStringList detectedBackends() const;
            /** If a backend can be started, reasonably, with no configuration.
             *
             * For example, FCGI can be started iff the FCGI socket is open,
             * and the HTTP one is pretty much always available.
             *
             * If there is evidence that the specified backend *should* be active
             * (rather than just "can be"), it should be listed in detectedBackends.
             */
            virtual bool requiresConfiguration(const QString& backend) const;

            virtual void configureHttpd(const QString& backend);
            bool start(const QString& backend);
        signals:
            void newRequest(Server::Request* request);
        protected slots:
            /** Create a new request with the given ClientIODevice.
             *
             * Note that 'device' may be deleted by this call.
             */
            void addRequest(ClientIODevice* device);
            void closeIfFinished();
        protected:
            virtual bool startBackend(const QString& backend) = 0;
            CommunicationInterface(QObject* parent);
            void addWorker(Worker* worker);
        private:
            ClientIODevice::HeaderMap m_extraHeaders;
    };
}

#endif // COMMUNICATIONINTERFACE_H
