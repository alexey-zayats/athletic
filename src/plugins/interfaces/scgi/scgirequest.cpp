#include "scgirequest.h"

#include <server/proxyclientiodevice.h>

#include <QDebug>
#include <QTcpSocket>

namespace Scgi
{
    Request::~Request()
    {
    }

    Request::Request( QTcpSocket* socket, QObject* parent)
        : Server::CommunicationInterface::Worker(parent)
    , m_socket(socket)
    {
        socket->setParent(this);
        socket->open(QIODevice::ReadWrite);
        Q_ASSERT(socket->isOpen());
        Q_ASSERT(socket->isReadable());
        Q_ASSERT(socket->isWritable());

        connect(
            socket,
            SIGNAL(readyRead()),
            SLOT(startResponse())
        );
    }

    void Request::cleanup()
    {
        m_socket->flush();
        m_socket->close();
        emit finished(thread());
        deleteLater();
    }

    void Request::startResponse()
    {
        // Netstring: "length:blob,"
        QString lengthString;
        Q_FOREVER
        {
            char character;
            const bool readCharacter= m_socket->getChar(&character);
            Q_ASSERT(readCharacter);
            if(character == ':' || !readCharacter)
            {
                break;
            }
            else
            {
                lengthString.append( QLatin1Char(character) );
            }
        }
        bool lengthIsNumeric;
        const unsigned int length = lengthString.toUInt(&lengthIsNumeric);
        Q_ASSERT(lengthIsNumeric);
        const QByteArray headerBlob = m_socket->read(length);
        Q_ASSERT(static_cast<qint64>(length) == headerBlob.length());
        m_socket->getChar(0); // skip ':' in netstring

        QList<QByteArray> parts = headerBlob.split(0);
        Q_ASSERT(parts.count() % 2); // null-terminated, last part is empty
        parts.takeLast();
        Server::ClientIODevice::HeaderMap headers;
        while(!parts.isEmpty())
        {
            const QByteArray name = parts.takeFirst();
            const QByteArray value = parts.takeFirst();
            headers.insert(name, value);
        }
        Q_ASSERT(headers.contains("CONTENT_LENGTH"));
        Q_ASSERT(headers.contains("SCGI"));
        Q_ASSERT(headers.value("SCGI") == "1");

        disconnect(m_socket, 0, this, 0);

        Server::ProxyClientIODevice* device = new Server::ProxyClientIODevice(headers, m_socket, this);
        connect(device, SIGNAL(destroyed(QObject*)), SLOT(cleanup()));
        emit newRequest(device);
    }
};
