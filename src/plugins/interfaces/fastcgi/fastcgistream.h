#ifndef FASTCGISTREAM_H
#define FASTCGISTREAM_H

#include <server/clientiodevice.h>

class QTcpSocket;

namespace FastCgi
{
    class Stream : public Server::ClientIODevice
    {
        Q_OBJECT
        public:
            Stream(const HeaderMap& headers, quint16 requestId, QTcpSocket* output, QObject* parent);
            ~Stream();

            bool waitForBytesWritten(int msec);
            qint64 bytesAvailable() const;
            qint64 pos() const;
            bool seek(qint64 pos);

            HeaderMap requestHeaders() const;

            /** Data needs to be appended by the socket manager, not directly read from the socket,
             * as FastCGI supports multiplexing.
             */
            void appendData(const QByteArray& data);

            bool isSequential() const;

        protected:
            /// Read data from buffer
            qint64 readData(char* data, qint64 maxSize);
            /// Write a FastCGI STDOUT record
            qint64 writeData(const char* data, qint64 maxSize);
        private:
            HeaderMap m_requestHeaders;
            QByteArray m_requestBuffer;
            qint64 m_requestBufferReadPosition;
            quint16 m_requestId;
            QTcpSocket* m_socket;
    };
}
#endif // FASTCGISTREAM_H
