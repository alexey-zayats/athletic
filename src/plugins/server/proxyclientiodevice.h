#ifndef PROXYCLIENTIODEVICE_H
#define PROXYCLIENTIODEVICE_H

#include "clientiodevice.h"
#include "server_global.h"

namespace Server
{
    /// @internal Simple ClientIODevice that just passes-through to another QIODevice.
    class SERVER_EXPORT ProxyClientIODevice: public ClientIODevice
    {
        Q_OBJECT
        public:
            ProxyClientIODevice(const HeaderMap& headers, QIODevice* source, QObject* parent);
            bool waitForBytesWritten(int msecs);
            HeaderMap requestHeaders() const;
        protected:
            qint64 readData(char* data, qint64 maxSize);
            qint64 writeData(const char* data, qint64 maxSize);
        private:
            HeaderMap m_headers;
            QIODevice* m_source;
    };
};
#endif // PROXYCLIENTIODEVICE_H
