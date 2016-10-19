#ifndef SOCKETFLUSHER_H
#define SOCKETFLUSHER_H

#include <QAbstractSocket>

#include "server_global.h"

namespace Server
{
    /** Class to cleanup a socket.
     *
     * Takes ownership, and automatically deletes both itself and the socket
     * when there's no more data to write to the socket.
     */
    class SERVER_EXPORT SocketFlusher : public QObject
    {
        Q_OBJECT
        public:
            SocketFlusher(QAbstractSocket* socket);
        private slots:
            void deleteIfFlushed();
        private:
            QAbstractSocket* m_socket;
    };
}
#endif // SOCKETFLUSHER_H
