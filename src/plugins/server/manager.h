#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QVariant>

namespace Server
{
    class Request;

    /** Class managing FastCGI connections.
     *
     * This class is responsible for listening to the FastCGI socket,
     * and acting on whatever data is received.
     *
     * @ingroup core
     */
    class Manager : public QObject
    {
        Q_OBJECT
        public:
            /** Create a Manager.
             *
             * This manager will read its' configuration files.
             *
             * @param parent is the parent object.
             */
            Manager(QObject* parent = 0);

            /** Create a Manager with the specified configuration.
             *
             * This should really only be used for embedding, or if you provide your own configuration interface.
             * It reduces flexibility.
             *
             * @param backend is the backend to use (eg 'HTTP', 'FCGI', and so on).
             * @param configuration is a key->QVariant mapping of configuration values that would be in the 'Server' section of the configuration file.
             * @param parent is the parent QObject.
             */
            Manager(const char* backend, const QMap<QString, QVariant>& configuration, QObject* parent = 0);
            /// Destroy the Manager.
            ~Manager();
        signals:
            void newRequest(Server::Request*);
        private:
            class Private;
            ///@internal
            Private* d;
    };
}
#endif // MANAGER_H
