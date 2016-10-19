#ifndef SCGIINTERFACE_H
#define SCGIINTERFACE_H

#include <server/communicationinterface.h>

class QTcpServer;

namespace Scgi
{
    class Interface : public Server::CommunicationInterface
    {
        Q_OBJECT
        public:
            /// Create a ScgiInterface object.
            Interface(QObject* parent = NULL);
            ~Interface();
            bool isFinished() const;
            QStringList backends() const;
            void configureHttpd(const QString& backend);
        protected:
            bool startBackend(const QString& backend);
        private slots:
            /// Request that the application shuts down.
            void shutdown();
            /// Spawn a new ScgiRequest
            void spawnRequest();
        private:
            QTcpServer* m_tcpServer;
    };
}

#endif // SCGIINTERFACE_H
