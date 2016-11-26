#ifndef ABSTRACTRESPONDER_H
#define ABSTRACTRESPONDER_H

#include <QObject>
#include "server_global.h"

namespace Server
{
    class Request;

    /** Interface for a QObject factory class.
     *
     * @see Spawner
     */
    class SERVER_EXPORT SpawnerBase {
        public:
            SpawnerBase();
            virtual QObject* spawn(QObject* parent) const = 0;
            virtual bool persist() const = 0;
            virtual ~SpawnerBase();
    };

    /** Template for a QObject factory class.
     *
     * @see SpawnerBase
     * @see ThreadedResponder
     */
    template<class T> class Spawner : public SpawnerBase
    {
        public:
            QObject* spawn(QObject* parent) const
            {
                return new T(parent);
            }
            bool persist() const
            {
                return false;
            }
    };

    /** Interface for responder classes, spawning instances of your object.
     *
     * @see BlockingResponder for a simple implementation, and @see ThreadedResponder
     * for a multi-threaded implementation.
     */
    class SERVER_EXPORT AbstractResponder : public QObject
    {
        Q_OBJECT
        public:
            AbstractResponder(QObject* parent);
            virtual ~AbstractResponder();

            virtual void respond(SpawnerBase* spawner, const char* responderSlot, Server::Request*) = 0;
        public slots:
            virtual void respond(Server::Request*) = 0;
    };
};
#endif // ABSTRACTRESPONDER_H
