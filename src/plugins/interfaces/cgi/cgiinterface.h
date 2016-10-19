#ifndef CGIINTERFACE_H
#define CGIINTERFACE_H

#include <server/communicationinterface.h>

namespace Cgi
{
    class Interface : public Server::CommunicationInterface
    {
        Q_OBJECT
        public:
            Interface(QObject* parent = 0);
            ~Interface();

            bool isFinished() const;
            QStringList backends() const;
            QStringList detectedBackends() const;
        protected:
            bool startBackend(const QString& backend);
        private slots:
            void init();
    };
}
#endif // CGIINTERFACE_H
