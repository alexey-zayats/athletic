#ifndef FASTCGIINTERFACE_H
#define FASTCGIINTERFACE_H

#include <server/communicationinterface.h>
#include <QStringList>

class QFileSystemWatcher;
class QSocketNotifier;

namespace FastCgi
{
    class SocketManager;
    class SocketServer;
    /** @internal
     * @brief Class managing new FastCGI connections.
     *
     * This class listens to the main FastCGI socket, spawns new
     * connections, and passes them off to a ServerSocketManager.
     *
     * It will spread the load over QThread::idealThreadCount() threads.
     */
    class Interface : public Server::CommunicationInterface
    {
        Q_OBJECT
        public:
            /// Create a Interface object.
            Interface(QObject* parent = NULL);
            ~Interface();
            bool isFinished() const;
            QStringList backends() const;
            QStringList detectedBackends() const;
            void configureHttpd(const QString& backend);
        protected:
            bool startBackend(const QString& backend);
        private slots:
            /// Accept a new FastCGI connection.
            void acceptNewConnection();
        private:
            SocketServer* m_socketServer;

    };
}
#endif // FASTCGIINTERFACE_H
