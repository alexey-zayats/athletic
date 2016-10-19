#include "cgirequest.h"

#include <QDebug>

#ifdef Q_OS_WIN32
#define environ _environ
#endif
#include <stdio.h>

extern char** environ;

namespace Cgi
{
    Request::Request(QObject* parent)
        : Server::ClientIODevice(parent)
    {
        open(QIODevice::ReadWrite | QIODevice::Unbuffered);
        // Read headers
        for(int i = 0; environ[i]; ++i)
        {
            QList<QByteArray> parts = QByteArray(environ[i]).split('=');
            if(parts.count() > 1)
            {
                const QByteArray key = parts.takeFirst();
                QByteArray value;
                Q_FOREVER
                {
                    value.append(parts.takeFirst());
                    if(!parts.isEmpty())
                    {
                        value.append('=');
                    }
                    else
                    {
                        break;
                    }
                }
                m_requestHeaders.insertMulti(key, value);
            }
        }
    }

    Request::~Request()
    {
        fflush(stdout);
    }

    Server::ClientIODevice::HeaderMap Request::requestHeaders() const
    {
        return m_requestHeaders;
    }

    qint64 Request::readData(char* data, qint64 maxSize)
    {
        return fread(data, 1, maxSize, stdin);
    }

    qint64 Request::writeData(const char* data, qint64 maxSize)
    {
        return fwrite(data, 1, maxSize, stdout);
    }
}
