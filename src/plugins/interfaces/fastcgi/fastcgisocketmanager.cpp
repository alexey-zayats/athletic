#include "fastcgisocketmanager.h"

#include "beginrequestrecord.h"
#include "endrequestrecord.h"

#include <server/enumhelpers.h>
#include "fastcgistream.h"
#include "parametersrecord.h"
#include "recordheader.h"
#include "standardinputrecord.h"

#include "fastcgi.h"

#include <QCoreApplication>
#include <QDebug>
#include <QMutexLocker>
#include <QSocketNotifier>
#include <QTcpSocket>
#include <QTimer>

namespace FastCgi
{
    SocketManager::SocketManager(QTcpSocket* socket, QObject* parent)
        : Server::CommunicationInterface::Worker(parent)
    {
        m_socket = socket;
        m_socket->setParent(this);

        connect(
            m_socket,
            SIGNAL(readyRead()),
            this,
            SLOT(processSocketData())
        );
    }

    SocketManager::~SocketManager()
    {
    }

    void SocketManager::processSocketData()
    {
        bool success;
        do
        {
            if(!m_recordHeader.isValid())
            {
                success = processNewRecord();
            }
            else
            {
                success = processRecordData();
            }
        }
        while(success && m_socket->bytesAvailable() > 0);
    }

    bool SocketManager::processRecordData()
    {
        RecordHeader header(m_recordHeader);

        if(m_socket->bytesAvailable() < header.payloadLength())
        {
            return false;
        }

        QByteArray data = m_socket->read(header.payloadLength());
        qint64 bytesRead = data.length();

        if(bytesRead != header.payloadLength())
        {
            qFatal("Couldn't read payload - tried to read %d bytes, got %lld", header.payloadLength(), bytesRead);
        }

        switch(header.type())
        {
            case RecordHeader::BeginRequestRecord:
                beginRequest(data);
                break;
            case RecordHeader::ParametersRecord:
                if(!loadParameters(data))
                {
                    respond();
                }
                break;
            case RecordHeader::StandardInputRecord:
                readStandardInput(data);
                break;
            default:
                qFatal("Don't know how to deal with payload for type %s", ENUM_DEBUG_STRING(RecordHeader,RecordType,header.type()));
        }
        m_recordHeader = RecordHeader();
        return true;
    }

    bool SocketManager::loadParameters(const QByteArray& data)
    {
        quint16 requestId = m_recordHeader.requestId();
        Q_ASSERT(m_recordHeader.type() == RecordHeader::ParametersRecord);
        ParametersRecord record(m_recordHeader, data);
        if(record.isEmpty())
        {
            return false;
        }
        else
        {
            m_requestHeaders[requestId].unite(record.parameters());
            return true;
        }
    }

    void SocketManager::readStandardInput(const QByteArray& data)
    {
        const quint16 requestId = m_recordHeader.requestId();
        Q_ASSERT(m_recordHeader.type() == RecordHeader::StandardInputRecord);
        QMutexLocker lock(&m_streamMutex);
        if(m_streams[requestId])
        {
            StandardInputRecord record(m_recordHeader, data);
            m_streams[requestId]->appendData(record.streamData());
        }
        // Otherwise, the request is dealt with, and the remaining standard input
        // was ignored.
    }

    void SocketManager::beginRequest(const QByteArray& data)
    {
        quint16 requestId = m_recordHeader.requestId();
        Q_ASSERT(m_recordHeader.type() == RecordHeader::BeginRequestRecord);

        BeginRequestRecord record(m_recordHeader, *reinterpret_cast<const FCGI_BeginRequestBody*>(data.constData()));
        Q_ASSERT(record.role() == BeginRequestRecord::ResponderRole);

        if(m_requestHeaders.size() <= requestId)
        {
            const int newSize = (requestId + 1) * 2;
            m_requestHeaders.resize(newSize);
            m_closeSocketOnExit.resize(newSize);
            m_streams.resize(newSize);
        }
        m_requestHeaders[requestId].clear();
        m_streams[requestId] = 0;
        m_closeSocketOnExit[requestId] = ! (record.flags() & BeginRequestRecord::KeepConnection);
    }

    void SocketManager::queueSocketCheck()
    {
        QTimer::singleShot(0, this, SLOT(processSocketData()));
    }

    void SocketManager::cleanupStream(QObject* _stream)
    {
        QMutexLocker lock(&m_streamMutex);
        Stream* stream = static_cast<Stream*>(_stream);
        Q_ASSERT(m_requestMap.contains(stream));
        const quint16 requestId = m_requestMap.value(stream);
        m_requestMap.remove(stream);

        // close and delete if the server's lazy
        if(m_closeSocketOnExit.value(requestId))
        {
            emit finished(thread());
            deleteLater();
        }
        m_requestHeaders[requestId].clear();
        m_streams[requestId] = 0;
    }

    void SocketManager::respond()
    {
        const quint16 requestId = m_recordHeader.requestId();
        Stream* stream = new Stream(m_requestHeaders[requestId], requestId, m_socket, this);
        m_requestMap.insert(stream, requestId);
        m_streams[requestId] = stream;

        connect(
            stream,
            SIGNAL(destroyed(QObject*)),
            SLOT(cleanupStream(QObject*))
        );

        // in case we have more local data...
        m_recordHeader = RecordHeader();
        queueSocketCheck();


        // actually start the response
        newRequest(stream);
    }

    bool SocketManager::processNewRecord()
    {
        if(m_socket->bytesAvailable() < FCGI_HEADER_LEN)
        {
            return false;
        }

        FCGI_Header fcgiHeader;
        qint64 bytesRead = m_socket->read(reinterpret_cast<char*>(&fcgiHeader), FCGI_HEADER_LEN);
        if(bytesRead != FCGI_HEADER_LEN)
        {
            qFatal("Couldn't read FCGI header - tried to read %d bytes, got %lld", FCGI_HEADER_LEN, bytesRead);
        }
        m_recordHeader = RecordHeader(fcgiHeader);
        if(m_socket->bytesAvailable() >= m_recordHeader.payloadLength())
        {
            processRecordData();
        }
        return true;
    }
}
