#ifndef CLIENTIODEVICE_H
#define CLIENTIODEVICE_H

#include <QHash>
#include <QIODevice>

#include "server_global.h"

namespace Server
{
    /** @internal Interface for accessing/sending client data.
     *
     * This provides access to the headers, and direct to POST data and response output as a stream (QIODevice).
     *
     * Response headers will be written as normal data, CGI-style. If the interface implemented by a subclass
     * doesn't support this, conversion must be done transparently (eg, translate Status: 200 OK to HTTP/1.1 200 OK)
     *
     * @ingroup core
     */
    class SERVER_EXPORT ClientIODevice: public QIODevice
    {
        Q_OBJECT
        public:
            typedef QHash<QByteArray, QByteArray> HeaderMap;
            /// Destructor.
            virtual ~ClientIODevice();

            /** All ClientIODevices should be assumed to be sequential.
             *
             * @returns true
             */
            bool isSequential() const;

            /// Return all (CGI-style) headers included in the request
            virtual HeaderMap requestHeaders() const = 0;
        protected:
            ClientIODevice(QObject* parent);
    };
}
#endif // CLIENTIODEVICE_H
