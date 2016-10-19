#include "fastcgistream.h"

#include "endrequestrecord.h"
#include <server/socketflusher.h>
#include "standardinputrecord.h"
#include "standardoutputrecord.h"

#include <server/memcpy_safe.h>

#include <QDebug>
#include <QTcpSocket>
#include <QThread>

#include "fastcgi.h"

namespace FastCgi
{
    Stream::Stream(const HeaderMap& headers, quint16 requestId, QTcpSocket* socket, QObject* parent)
    : Server::ClientIODevice(parent)
    , m_requestHeaders(headers)
    , m_requestBufferReadPosition(0)
    , m_requestId(requestId)
    , m_socket(socket)
    {
        m_socket->setParent(this);
        open(QIODevice::ReadWrite | QIODevice::Unbuffered);
        connect(
            m_socket,
            SIGNAL(aboutToClose()),
            SIGNAL(aboutToClose())
        );
    }

    Server::ClientIODevice::HeaderMap Stream::requestHeaders() const
    {
        return m_requestHeaders;
    }

    qint64 Stream::bytesAvailable() const
    {
        return m_requestBuffer.length() - m_requestBufferReadPosition;
    }

    void Stream::appendData(const QByteArray& data)
    {
        m_requestBuffer.append(data);
        emit readyRead();
    }

    Stream::~Stream()
    {
        m_socket->write(EndRequestRecord::create(m_requestId));
        new Server::SocketFlusher(m_socket);
    }

    qint64 Stream::readData(char* data, qint64 maxSize)
    {
        const qint64 toRead = qMin(m_requestBuffer.length() - m_requestBufferReadPosition, maxSize);
        if(toRead >= 0 && ::memcpy_safe(data, maxSize, m_requestBuffer.constData(), toRead))
        {
            m_requestBufferReadPosition += toRead;
            return toRead;
        }
        else
        {
            return -1;
        }
    }

    qint64 Stream::writeData(const char* data, qint64 dataSize)
    {
        Q_ASSERT(thread() == m_socket->thread());
        Q_ASSERT(thread() == QThread::currentThread());
        qint64 remaining = dataSize;
        while(remaining > 0)
        {
            const qint64 toWrite(qMin(remaining, static_cast<qint64>(65535)));
            const qint64 offset(dataSize - remaining);

            QByteArray record = StandardOutputRecord::create(
                m_requestId,
                QByteArray(&data[offset], toWrite)
            );
            qint64 wrote = m_socket->write(record);
            QTcpSocket* socket = qobject_cast<QTcpSocket*>(m_socket);
            Q_ASSERT(socket);
            if(!waitForBytesWritten(1000))
            {
                if(socket->state() != QTcpSocket::ConnectedState)
                {
                    return -1;
                }
                qFatal("Couldn't write to socket: %s %d", qPrintable(m_socket->errorString()), m_socket->isOpen());
            }
            Q_ASSERT(wrote == record.length());
            if(wrote != record.length())
            {
                qDebug() << "LENGTH MISMATCH";
                return -1;
            }
            remaining -= toWrite;
        }
        return dataSize;
    }

    bool Stream::waitForBytesWritten(int msecs)
    {
        QTcpSocket* socket = qobject_cast<QTcpSocket*>(m_socket);
        Q_ASSERT(socket);
        if(socket->state() != QTcpSocket::ConnectedState)
        {
            return false;
        }
        return m_socket->waitForBytesWritten(msecs);
    }
};
