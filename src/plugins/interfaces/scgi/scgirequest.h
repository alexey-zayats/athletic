#ifndef SCGIREQUEST_H
#define SCGIREQUEST_H

#include <server/communicationinterface_worker.h>

class QTcpSocket;

namespace Scgi
{
    class Request : public Server::CommunicationInterface::Worker
    {
        Q_OBJECT
        public:
            Request(QTcpSocket* socket, QObject* parent);
            ~Request();
        private slots:
            void startResponse();
            void cleanup();
        private:

            QTcpSocket* m_socket;
    };
}

#endif // SCGIREQUEST_H
