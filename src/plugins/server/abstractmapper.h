#ifndef FASTCGI_ABSTRACTMAPPER
#define FASTCGI_ABSTRACTMAPPER

#include "abstractresponder.h"

namespace AppSrv
{
    /** Map requests to services.
     *
     * This class is for mapping URLs to QObjects and slots.
     *
     * @see AbstractMapper
     * @ingroup services
     */
    class AbstractMapper: public QObject
    {
        Q_OBJECT
        public:
            enum ResponseMode
            {
                BlockingResponses,
                ThreadedResponses
            };

            AbstractMapper(ResponseMode mode = BlockingResponses, QObject* parent = 0);
            virtual ~AbstractMapper();

            /// Add a spawner to the mapping.
            void addMapping(const QString& serviceName, SpawnerBase* spawner, const char* slot);
            /** Add a slot to the mapping.
             *
             * The receiver *MUST NOT* have a parent, and *MUST* be threadsafe.
             */
            void addMapping(const QString& serviceName, QObject* receiver, const char* slot);
        public slots:
            void respond(AppSrv::Request*);
        protected:
            /** Return which of the specified service names match.
             *
             * @p services is a QBytearray containing the service names, in percent-encoded UTF-8.
             */
            virtual int indexIn(const QList<QByteArray>& services) const = 0;
        private:
            class Private;
            Private* d;
    };
}
#endif // FASTCGI_ABSTRACTMAPPER
