#include "request.h"
#include "request_private.h"

#include "uploadedfile.h"

#include <QDebug>
#include <QNetworkCookie>
#include <QRegExp>
#include <QUrl>


namespace Server
{
    Request::Request(Private* _d, QObject* parent)
    : QIODevice(parent)
    , d(_d)
    {
        open(QIODevice::ReadWrite);
        d->device->setParent(this);
        connect(
            d->device,
            SIGNAL(readyRead()),
            this,
            SIGNAL(readyRead())
        );
    }

    bool Request::atEnd() const
    {
        const bool atEnd = d->device->atEnd() && QIODevice::atEnd();
        return atEnd;
    }

    bool Request::isSequential() const
    {
        return true;
    }

    qint64 Request::readData(char* data, qint64 maxSize)
    {
        Q_ASSERT(d->postDataMode == Private::UnknownPostData || d->postDataMode == Private::RawPostData);
        d->postDataMode = Private::RawPostData;
        Q_ASSERT(d->device->isOpen());
        Q_ASSERT(d->device->isReadable());
        const qint64 bytesRead = d->device->read(data, maxSize);
        return bytesRead;
    }

    qint64 Request::writeData(const char* data, qint64 maxSize)
    {
        QIODevice* device = d->device;

        if(!d->haveSentHeaders)
        {
            d->haveSentHeaders = true;
            for(ClientIODevice::HeaderMap::ConstIterator it = d->responseHeaders.constBegin(); it != d->responseHeaders.constEnd(); ++it)
            {
                device->write(it.key());
                device->write(": ");
                device->write(it.value());
                device->write("\r\n");
            }
            device->write("\r\n");
        }
        return device->write(data, maxSize);
    }

    qint64 Request::size() const
    {
        return QString::fromLatin1(rawValue(ServerData, "CONTENT_LENGTH")).toLongLong();
    }

    QUrl Request::url(UrlPart part) const
    {
        QUrl url;
        // Protocol and host are needed, regardless of part
        if(rawValue(ServerData,"HTTPS") == "on")
        {
            url.setScheme( QLatin1String("https") );
        }
        else
        {
            url.setScheme( QLatin1String("http") );
        }
        // authority == user:password@host:port - as HTTP_HOST contains user and port, go with that
        url.setAuthority(value(ServerData, "HTTP_HOST"));

        const int queryStringOffset = rawValue(ServerData, "REQUEST_URI").contains('?') ? 1 : 0;
        const int queryStringLength = rawValue(ServerData, "QUERY_STRING").length() + queryStringOffset;
        switch(part)
        {
            case RootUrl:
            {
                const int pathInfoLength = rawValue(ServerData, "PATH_INFO").length();
                QByteArray basePath = rawValue(ServerData, "REQUEST_URI");
                basePath.chop(queryStringLength + pathInfoLength);
                url.setPath( QLatin1String(basePath),
                            QUrl::DecodedMode);
                break;
            }
            case LocationUrl:
            case RequestUrl:
            {
                QByteArray basePath = rawValue(ServerData, "REQUEST_URI");
                basePath.chop(queryStringLength);
                url.setPath( QLatin1String(basePath),
                            QUrl::DecodedMode);
                if(part == RequestUrl)
                {
                    url.setQuery( QLatin1String( rawValue(ServerData, "QUERY_STRING") ),
                                 QUrl::DecodedMode);
                }
                break;
            }
            default:
                qFatal("Unknown URL part: %d", part);
        }
        return url;
    }

    QList<QNetworkCookie> Request::cookies() const
    {
        QList<QNetworkCookie> cookies;
        for(ClientIODevice::HeaderMap::ConstIterator it = d->serverData.constBegin(); it != d->serverData.constEnd(); ++it)
        {
            if(it.key().toUpper() == "HTTP_COOKIE")
            {
                QList<QByteArray> list = it.value().split(';');
                for(int i = 0; i < list.length(); ++i)
                {
                    cookies.append(QNetworkCookie::parseCookies(list.at(i)));
                }
            }
        }
        return cookies;
    }

    void Request::sendCookie(const QNetworkCookie& cookie)
    {
        addHeader("set-cookie", cookie.toRawForm());
    }

    void Request::setHeader(const QByteArray& name, const QByteArray& value)
    {
        Q_ASSERT(!d->haveSentHeaders);
        d->responseHeaders[name] = value;
    }

    void Request::addHeader(const QByteArray& name, const QByteArray& value)
    {
        Q_ASSERT(!d->haveSentHeaders);
        d->responseHeaders.insertMulti(name, value);
    }

    QByteArray Request::responseHeader(const QByteArray& name)
    {
        return d->responseHeaders.value(name);
    }

    QHash<QByteArray, QByteArray> Request::rawValues(DataSource source) const
    {
        switch(source)
        {
            case GetData:
                return d->getData;
            case PostData:
                d->loadPostVariables();
                return d->postData;
            case ServerData:
                return d->serverData;
            default:
                qFatal("Unknown value type: %d", source);
        }
        return QHash<QByteArray, QByteArray>();
    }

    QByteArray Request::rawValue(DataSource source, const QByteArray& name) const
    {
        return rawValues(source).value(name);
    }

    QString Request::value(DataSource source, const QByteArray& name) const
    {
        return QUrl::fromPercentEncoding(rawValue(source, name));
    }

    UploadedFile *Request::fileUpload(const QByteArray &name)
    {
        if ( d->m_uploads.contains(name) )
            return d->m_uploads.value(name);
        else
            return 0;
    }

    Request::~Request()
    {
        emit finished(this);
        delete d;
    }
}
