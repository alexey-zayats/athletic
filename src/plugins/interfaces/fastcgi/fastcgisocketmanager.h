#ifndef FASTCGISOCKETMANAGER_H
#define FASTCGISOCKETMANAGER_H

#include <server/communicationinterface_worker.h>
#include <server/clientiodevice.h>

#include "recordheader.h"

#include <QHash>
#include <QMutex>

class QTcpSocket;

namespace FastCgi
{
    class Stream;
    /** @internal
     * @brief Class managing all FastCGI requests on a specified socket.
     *
     * If requested by the web server, this will delete itself, and close
     * the socket.
     *
     * There can be multiple simultaneous requests over one socket.
     */
    class SocketManager : public Server::CommunicationInterface::Worker
    {
        Q_OBJECT
        public:
            /** Create a SocketManager.
             * @param socketId is the file descriptor for a socket.
             * @param parent is a parent object.
             */
            SocketManager(QTcpSocket* socket, QObject* parent = NULL);
            /// Destroy this socket manager.
            ~SocketManager();
        private:
            /// Put a call to processSocketData() into the event queue.
            void queueSocketCheck();

            /// Process the header of a FastCGI record.
            bool processNewRecord();
            /** Process the data of a FastCGI record.
             *
             * This will call one out of beginRequest,
             * loadParameters(), or readStandardInput(), depending
             * on the record type given in the header.
             *
             * Once an empty parameters record has been received, it
             * will call respond().
             */
            bool processRecordData();
            /// Start a new request.
            void beginRequest(const QByteArray& data);
            /// Process a parameters record.
            bool loadParameters(const QByteArray& data);
            /// Process a STDIN record.
            void readStandardInput(const QByteArray& data);
            /// Create a Responder, run it, and cleanup.
            void respond();
        private slots:
            /** Process new data on the socket.
             *
             * If there is sufficient data, this will call either
             * processNewRecord() or processRecordData(), depending
             * on the current state.
             */
            void processSocketData();
            void cleanupStream(QObject* stream);
        private:
            /// The header of the current record.
            RecordHeader m_recordHeader;
            /// The socket this SocketManager managers.
            QTcpSocket* m_socket;

            // FastCGI spec says request IDs will be tightly packed near zero.

            /** The headers for requests currently being processed.
             *
             * This is indexed by request id.
             */
            QVector<Server::ClientIODevice::HeaderMap> m_requestHeaders;
            QVector<Stream*> m_streams;

            /** If the socket is supposed to be closed.
             *
             * This is indexed by request id.
             *
             * If a value is true, once the request ID in
             * question has been processed, deleteLater() will be
             * called on this object.
             */
            QVector<bool> m_closeSocketOnExit;

            /// Responder -> requestId map
            QHash<Stream*, quint64> m_requestMap;

            /// Lock changing of m_streams;
            QMutex m_streamMutex;
    };
}
#endif // FASTCGISOCKETMANAGER_H
