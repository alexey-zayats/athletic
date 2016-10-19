#ifndef SERVICE_PRIVATE_H
#define SERVICE_PRIVATE_H

#include "caches.h"
#include "filecache.h"
#include "filedependentcache.h"
#include "request.h"

#include <QFileSystemWatcher>
#include <QList>
#include <QMutex>
#include <QPair>
#include <QRegExp>

class QMetaMethod;
namespace Server
{
    class Service::Private
    {
        public:
            Private();
            void invokeMethod(
                QObject* object,
                const char* slot,
                const QStringList& parameters
            );
            bool dispatchingRequest;
            bool canCacheThisRequest;
            QString cacheKey;
            Request* request;
            bool usingFileCache;
        private:
            // scope guard
            Caches m_caches;
    };
}
#endif // SERVICE_PRIVATE_H
