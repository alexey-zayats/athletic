#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <server/clientiodevice.h>

#include <QStringList>

class QTcpSocket;

namespace Http
{
    class Request : public Server::ClientIODevice
    {
        Q_OBJECT
        public:
            Request(const HeaderMap& standardRequestHeaders,
                        const HeaderMap& standardResponseHeaders,
                        const QStringList& staticDirectories,
                        QTcpSocket* socket,
                        QObject* parent);
            ~Request();
            HeaderMap requestHeaders() const;
            virtual bool atEnd() const;
        signals:
            void gotHeaders(Request*);
        protected:
            qint64 readData(char* data, qint64 maxSize);
            qint64 writeData(const char* data, qint64 maxSize);
        private slots:
            void readSocketData();
        private:
            /** We've got all the headers, dispatch the request.
             *
             * This either passes off the request to Server, or, if it's in
             * m_staticDirectories, serves the file raw.
             */
            void dispatchRequest();
            enum RequestState
            {
                WaitingForRequest, ///< We've not actually received the "$VERB $URL HTTP/$VERSION" line yet.
                WaitingForRequestHeaders, ///< We might have recieved some headers, but not all of them (i.e. no \r\n\r\n yet).
                WaitingForRequestBody ///< Not actually expecting anything new; if we get it, it's POST data.
            };
            enum ResponseState
            {
                WaitingForResponseHeaders, ///< We've not received a \r\n from Server yet
                WaitingForResponseBody ///< We're dealing with content now
            };
            RequestState m_requestState;
            ResponseState m_responseState;

            HeaderMap m_requestHeaders;
            HeaderMap m_responseHeaders;

            QTcpSocket* m_socket;

            QStringList m_staticDirectories;

            QByteArray m_headerBuffer;
            qint64 m_headerBufferPosition;
    };
}

#endif // HTTPREQUEST_H
