#ifndef MANAGER_PRIVATE_H
#define MANAGER_PRIVATE_H

#include "caches.h"
#include "communicationinterface.h"
#include "manager.h"

#include <QObject>

class QFileSystemWatcher;
class QSettings;

namespace Server
{
    class Request;

    /** @internal
     * @brief Class doing main application setup.
     *
     * This sets up caches, and sets up a CommunicationInterface, such
     * as ServerInterface.
     */
    class Manager::Private : public QObject
    {
        Q_OBJECT
        public:
            /// Create a ManagerPrivate object.
            Private(QObject* parent = NULL);
            ~Private();
        signals:
            void newRequest(Server::Request* request);
        private slots:
            /// Request that the application shuts down.
            void shutdown();
        private:
            /// Show CLI for configuring the way Server communicates with the web server
            void configureHttpd();
            /// Show CLI for configuring the database
            void configureDatabase();

            /// Watcher to call shutdown() if the executable is modified.
            QFileSystemWatcher* m_applicationWatcher;

            /// Scope guard to create and cleanup global caches
            Caches* m_caches;

            CommunicationInterface* m_interface;

            QList<CommunicationInterface*> m_interfaces;
            QSettings *settings;
    };
};
#endif // MANAGER_PRIVATE_H
