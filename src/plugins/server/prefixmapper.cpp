#include "prefixmapper.h"

#include "blockingresponder.h"
#include "prefixmapper_private.h"
#include "prespawnedspawner.h"
#include "request.h"
#include "threadedresponder.h"

#include <QTextStream>
#include <QUrl>

namespace Server
{
    PrefixMapper::PrefixMapper(ResponseMode mode, QObject* parent)
    : QObject(parent)
    , d(new Private())
    {
        d->responder = 0;
        switch(mode)
        {
            case BlockingResponses:
                d->responder = new BlockingResponder(0, 0, this);
                break;
            case ThreadedResponses:
                d->responder = new ThreadedResponder(0, 0, this);
                break;
        }
        Q_ASSERT(d->responder);
    }

    void PrefixMapper::addMapping(const QString& serviceName, SpawnerBase* spawner, const char* slot)
    {
        d->services.insert(QUrl::toPercentEncoding(serviceName), Private::Receiver(spawner, slot));
    }

    void PrefixMapper::addMapping(const QString& serviceName, QObject* receiver, const char* slot)
    {
        d->services.insert(QUrl::toPercentEncoding(serviceName), Private::Receiver(new PrespawnedSpawner(receiver), slot));
    }

    QByteArray PrefixMapper::prefix(Server::Request* request)
    {
        return Private::prefix(request);
    }

    QByteArray PrefixMapper::suffix(Server::Request* request)
    {
        return Private::suffix(request);
    }

    void PrefixMapper::respond(Server::Request* request)
    {
        const QByteArray currentSuffix = Private::suffix(request);
        QList<QByteArray> parts = QByteArray(&currentSuffix.constData()[1], currentSuffix.length() - 1).split('/');
        const QByteArray serviceName(parts.isEmpty() ? QByteArray() : parts.takeFirst());

        Private::Receiver receiver = d->services.value(serviceName);
        QByteArray newPrefix = serviceName;
        if(!receiver)
        {
            receiver = d->services.value(QByteArray());
            parts.prepend(newPrefix);
            newPrefix.clear();
        }

        if(receiver)
        {
            const QByteArray currentPrefix = Private::prefix(request);
            if(currentPrefix.isEmpty())
            {
                Private::setPrefix(request, '/' + newPrefix);
            }
            else
            {
                Private::setPrefix(request, currentPrefix + '/' + newPrefix);
            }
            QByteArray suffix;
            if ( parts.size() ) {
                Q_FOREACH(const QByteArray& part, parts)
                {
                    suffix.append('/');
                    suffix.append(part);
                }
            } else {
                suffix = QByteArray("");
            }
            Private::setSuffix(request, suffix);

            d->responder->respond(receiver.spawner, receiver.slot, request);
        }
        else
        {
            qWarning("404 on request for '%s' ('%s'/'%s') - service: %s",
                     request->url(RequestUrl).toEncoded().constData(),
                     Private::prefix(request).constData(),
                     Private::suffix(request).constData(),
                     serviceName.constData());
            request->setHeader("STATUS", "404 Not Found");
            QTextStream out(request);
            out << tr("<h1>404 Not Found</h1><p>The page you are looking for could not be found.</p>") << endl;
        }
        return;
    }

    PrefixMapper::~PrefixMapper()
    {
        delete d;
    }
}
