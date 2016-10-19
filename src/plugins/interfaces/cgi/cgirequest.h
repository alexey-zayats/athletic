#ifndef CGIREQUEST_H
#define CGIREQUEST_H

#include <server/clientiodevice.h>

namespace Cgi
{
    class Request : public Server::ClientIODevice
    {
        Q_OBJECT
        public:
            Request(QObject* parent);
            ~Request();
            HeaderMap requestHeaders() const;
        protected:
            qint64 readData(char* data, qint64 maxSize);
            qint64 writeData(const char* data, qint64 maxSize);
        private:
            HeaderMap m_requestHeaders;
    };
}
#endif // CGIREQUEST_H
