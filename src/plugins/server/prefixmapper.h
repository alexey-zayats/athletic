#ifndef PREFIXMAPPER_H
#define PREFIXMAPPER_H

#include "abstractresponder.h"

namespace Server
{
    /** Map requests to services.
     *
     * This class is for mapping URLs to QObjects and slots.
     *
     * @see Service
     * @ingroup services
     */
    class PrefixMapper: public QObject
    {
        Q_OBJECT
        public:
            enum ResponseMode
            {
                BlockingResponses,
                ThreadedResponses
            };

            PrefixMapper(ResponseMode mode = BlockingResponses, QObject* parent = 0);
            virtual ~PrefixMapper();

            /// Add a spawner to the mapping.
            void addMapping(const QString& serviceName, SpawnerBase* spawner, const char* slot);
            /** Add a slot to the mapping.
             *
             * The receiver *MUST NOT* have a parent, and *MUST* be threadsafe.
             */
            void addMapping(const QString& serviceName, QObject* receiver, const char* slot);

            static QByteArray prefix(Server::Request* request);
            /// Nearly the same thing as PATH_INFO on the other side of PrefixMapper
            static QByteArray suffix(Server::Request* request);
        public slots:
            void respond(Server::Request*);
        private:
            class Private;
            Private* d;
    };
}
#endif // PREFIXMAPPER_H
