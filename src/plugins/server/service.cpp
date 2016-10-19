#include "service.h"

#include "caches.h"
#include "prefixmapper.h"
#include "service_private.h"

#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QGenericArgument>
#include <QMetaMethod>
#include <QMetaObject>
#include <QStringList>

#include <memory> //std::auto_ptr TODO replace with QScopedPointer in Qt 4.6

namespace Server
{
    Service::Service(QObject* parent)
    : QObject(parent)
    {
        d = new Service::Private();
    }

    Request* Service::request() const
    {
        return d->request;
    }

    Service::Private::Private()
        :
            dispatchingRequest(false),
            usingFileCache(false)
    {
    }

    /**@todo move this stuff to somewhere else
    QByteArray Service::readFile(const QString& path, bool useCache)
    {
        const QString prefix = path.startsWith('/') ? "" : QCoreApplication::applicationDirPath() + "/";
        const QString fullPath = prefix + path;

        if(d->canCacheThisRequest)
        {
            // not if use-cache:
            // if caching of this file isn't wanted, then surely the
            // request cache should be invalidated here too
            Caches::requestCache().addDependency(d->cacheKey, fullPath);
        }

        if(useCache)
        {
            CacheEntry entry = Caches::fileCache().value(fullPath);
            if(entry.isValid())
            {
                return entry.data();
            }
        }

        QFile file(fullPath);
        file.open(QIODevice::ReadOnly);
        Q_ASSERT(file.isOpen());

        if(this->usingFileCache() && useCache)
        {
            const QByteArray data(file.readAll());
            Caches::fileCache().setValue(fullPath, CacheEntry(QDateTime::currentDateTime(), data));
            return data;
        }
        else
        {
            return file.readAll();
        }
    }
    */

    void Service::cacheThisRequest()
    {
        ///@fixme Needs implementation
        /*
        OutputDevice* outputDevice = qobject_cast<OutputDevice*>(out.device());
        Q_ASSERT(outputDevice);
        Q_ASSERT(!outputDevice->haveSentData());
        outputDevice->setMode(OutputDevice::Logged);
        d->canCacheThisRequest = true;
        */
    }

    void Service::respond(Server::Request* request)
    {
        const QByteArray urlFragment = PrefixMapper::suffix(request);
        // Don't stack-overflow if a subclass calls the wrong function
        if(d->dispatchingRequest)
        {
            qFatal(
                "Recursion detected in Server::Service::dispatchRequest(). "
                "You probably have a subclass calling dispatchRequest which "
                "should be calling dispatchUncachedRequest instead."
            );
            return;
        }
        d->request = request;
        d->canCacheThisRequest = false;

        // Lookup this page in the cache
        d->cacheKey = QString( QLatin1String("%1::%2") )
                .arg( QLatin1String(metaObject()->className()) )
                .arg(QLatin1String(urlFragment));

        /**@fixme (caching)
        OutputDevice* outputDevice = qobject_cast<OutputDevice*>(out.device());
        Q_ASSERT(outputDevice);

        const CacheEntry entry(Caches::requestCache().value(d->cacheKey));
        if(entry.isValid() && !isExpired(urlFragment, entry.timeStamp()))
        {
            outputDevice->setSendingHeadersEnabled(false);
            outputDevice->write(entry.data());
            return;
        }*/

        d->dispatchingRequest = true;
        dispatchUncachedRequest(urlFragment);
    }

    void Service::dispatchUncachedRequest(const QByteArray& suffix)
    {
        const QString urlFragment = QUrl::fromPercentEncoding(suffix.mid(1));
        const UrlMap urlMap = this->urlMap();
        const char* slot = 0;
        QStringList parameters;

        for(
            QList<QPair<QString, const char*> >::ConstIterator it = urlMap.constBegin();
            it != urlMap.constEnd();
            ++it
        )
        {
            QRegExp re(it->first);
            if(re.exactMatch(urlFragment))
            {
                parameters = re.capturedTexts();
                parameters.takeFirst();
                slot = it->second;
                break;
            }
            else if(it->first.isNull() && !slot)
            {
                slot = it->second;
            }
        }
        if(slot)
        {
            d->invokeMethod(
                this,
                slot,
                parameters
            );
            if(!request()->parent())
            {
                d->dispatchingRequest = false;
            }
        }
        else
        {
            ///@todo Add some kind of interface for hooking 404s ?
            request()->setHeader("STATUS", "404 Not Found");
            QTextStream out(request());
            out << "<h1>404 Not Found</h1>";
            d->dispatchingRequest = false;
        }
    }

    void Service::Private::invokeMethod(
        QObject* object,
        const char* slot,
        const QStringList& parameters
    )
    {
        ///@todo check arguments
        Q_ASSERT(parameters.count() < 10); // QMetaMethod limitation
        Q_ASSERT(slot[0] == SLOT("bar")[0]); // check slot code
        ++slot; // chop off the code
        const int slotIndex = object->metaObject()->indexOfSlot(slot);
        Q_ASSERT(slotIndex != -1);
        const QMetaMethod method = object->metaObject()->method(slotIndex);

        // Sort out the arguments
        QList<QByteArray> parameterTypes = method.parameterTypes();
        Q_ASSERT(parameterTypes.count() == parameters.count());
        QGenericArgument arguments[10];
        for(int i = 0; i < parameters.count(); ++i)
        {
            Q_ASSERT(parameterTypes.at(i) == "QString");
            arguments[i] = Q_ARG(QString, parameters.at(i));
        }
        method.invoke(
            object,
            arguments[0],
            arguments[1],
            arguments[2],
            arguments[3],
            arguments[4],
            arguments[5],
            arguments[6],
            arguments[7],
            arguments[8],
            arguments[9]
        );
    }

    /*
    bool Service::usingFileCache()
    {
        return d->usingFileCache;
    }

    void Service::setUsingFileCache(bool useFileCache)
    {
        d->usingFileCache = useFileCache;
    }
    */

    Service::~Service()
    {
        d->dispatchingRequest = false;

        /**@fixme (caching)
        if(d->canCacheThisRequest)
        {
            Caches::requestCache().setValue(d->cacheKey, CacheEntry(QDateTime::currentDateTime(), qobject_cast<OutputDevice*>(out.device())->buffer()));
        }
        */

        delete d;
    }

    bool Service::isExpired(const QString& urlFragment, const QDateTime& generated)
    {
        Q_UNUSED(urlFragment);
        Q_UNUSED(generated);
        return false;
    }

    void Service::UrlMap::append(const QString& regexp, const char* slot)
    {
        QList<QPair<QString, const char*> >::append(qMakePair(regexp, slot));
    }

}
