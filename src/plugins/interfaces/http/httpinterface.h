#ifndef HTTPINTERFACE_H
#define HTTPINTERFACE_H

#include <server/communicationinterface.h>

class QTcpServer;

namespace Http
{
    class Request;
    class Interface : public Server::CommunicationInterface
    {
        Q_OBJECT
        public:
            /// Create a HttpInterface object.
            Interface(QObject* parent = NULL);
            ~Interface();
            bool isFinished() const;
            QStringList backends() const;
            virtual bool requiresConfiguration(const QString& backend) const;
            void configureHttpd(const QString& backend);
        protected:
            bool startBackend(const QString& backend);
        private slots:
            void startResponse();
            void announceRequest(Request* request);
        private:
            QTcpServer* m_server;
            QString m_staticDirectory;
    };
}

#endif // HTTPINTERFACE_H
