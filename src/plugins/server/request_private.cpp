#include "request_private.h"
#include "mimemultipartstreamreader.h"

#include <QCoreApplication>
#include <QDebug>
#include <QHash>
#include <QPair>
#include <QTime>
#include <QUrlQuery>

namespace Server
{
    Request::Private::Private(ClientIODevice* d)
    : device(d)
    , haveSentHeaders(false)
    , postDataMode(UnknownPostData)
    , serverData(d->requestHeaders())
    {
        d->open(QIODevice::ReadWrite | QIODevice::Unbuffered);
        getData = parseUrlEncoded(serverData.value("QUERY_STRING"));
        // Default header values:
        responseHeaders.insert("STATUS", "200 OK");
        responseHeaders.insert("CONTENT-TYPE", "text/html; charset=UTF-8");

        QByteArray uri = serverData["REQUEST_URI"];
        serverData.insert("PATH_INFO", uri.mid(0, (uri.indexOf('?') + 1) - 1));
    }

    Request::Private::~Private()
    {
        delete device;
    }

    ClientIODevice::HeaderMap Request::Private::parseUrlEncoded(QByteArray data)
    {
        ClientIODevice::HeaderMap out;
        QUrlQuery queryStringParser;
        queryStringParser.setQuery( QLatin1String(data) );

        typedef QPair<QString, QString> Pair;
        Q_FOREACH( Pair header, queryStringParser.queryItems())
            out.insert(header.first.toLocal8Bit(), header.second.toLocal8Bit());

        return out;
    }
    void Request::Private::parsePostData()
    {
        postData = parseUrlEncoded(device->readAll());
    }

    void Request::Private::parseMultipart() {
        //TODO: entitie too large

        QString contentType( QLatin1String( serverData.value("CONTENT_TYPE") ) );
        Q_ASSERT (!contentType.isEmpty());
        QString boundary = contentType.split(QLatin1String("; "))[1];
        boundary.replace(QLatin1String("\""), QLatin1String(""));
        boundary.replace(QLatin1String("boundary="), QLatin1String(""));

        Q_ASSERT(!boundary.isNull());

        QByteArray cdKey("Content-Disposition");

        while ( device->bytesAvailable() )
        {
            // we assume that every time at that poin we read boundary from device
            QByteArray line = device->readLine().trimmed();
            // if boundary contains '--' at the and we are done
            int ep = line.indexOf("--", boundary.size() );
            if ( ep > -1 )
                break;

            Q_ASSERT( line != boundary.toLocal8Bit() );

            // read all headers for part of data
            QHash<QByteArray,QByteArray> headers;
            while ( !(line = device->readLine().trimmed()).isEmpty() ) {
                int colonPos = line.indexOf(':');
                if (colonPos == -1 )
                    break;
                QByteArray hkey = line.mid(0, colonPos);
                QByteArray hvalue = line.mid(colonPos+2, line.size() - hkey.size() - 2 );
                headers.insert(hkey, hvalue);
            }

            if ( !headers.contains(cdKey) )
                continue;

            QByteArray cd = headers.value(cdKey);

            int s = 0;
            int idx = 0;

            QByteArray name, filename, value;

            while ( (idx = cd.indexOf("; ", s)) > -1 )
            {
                s = idx + 2;
                QByteArray pair = cd.mid( s, cd.size() - idx - 2);
                QList<QByteArray> parts = pair.split('=');

                if (parts[0] == QByteArray("name")) {
                    int a = parts[1].indexOf('"');
                    int b = parts[1].indexOf('"', a+1);
                    name = parts[1].mid(a+1, (parts[1].size() - (a+1)) - (parts[1].size()-b));
                }
                if (parts[0] == QByteArray("filename")) {
                    int a = parts[1].indexOf('"');
                    int b = parts[1].indexOf('"', a+1);
                    filename = parts[1].mid(a+1, (parts[1].size() - (a+1)) - (parts[1].size()-b));
                }

                if (filename.isNull()){
                    value = device->readLine().trimmed();
                    postData.insert(name, value);
                    continue;
                }

                postData.insert(name, filename);

                //TODO: read as upload
            }
        }
    }

    void Request::Private::loadPostVariables()
    {
        switch(postDataMode)
        {
            case RawPostData:
                qFatal("Tried to read post variables after reading raw post data.");
                break;
            case ValuesPostData:
                // already loaded
                break;
            case UnknownPostData:
                postDataMode = ValuesPostData;
                 ///@todo pay attention if content-type includes "; charset=FOO" - at the moment, assume UTF8
                 if(serverData.values("CONTENT_TYPE").startsWith("application/x-www-form-urlencoded"))
                     parsePostData();
                 else
                     parseMultipart();
                break;
        }
    }
}
