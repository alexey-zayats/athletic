#ifndef FILE_CACHE_H
#define FILE_CACHE_H

#include "filedependentcache.h"

#include <QHash>
#include <QMutex>
#include <QObject>
#include <QPointer>

class QFileSystemWatcher;

namespace Server
{
    /** @internal @brief Subclass of Cache specifically designed for keeping caches of local files.
     *
     * This class uses QFileSystemWatcher to watch all files in the cache,
     * and remove them from the cache as soon as they are modified.
     */
    class FileCache: public FileDependentCache
    {
        Q_OBJECT
        public:
            /// Create a FileCache.
            FileCache(const QString& cacheName, QObject* parent = NULL);
            /// Add an entry to the cache, and start watching it.
            void setValue(const QString& path, const CacheEntry& object);
        public slots:
            /// Remove an entry and stop watching it.
            void remove(const QString& path);
    };
}

#endif // FILE_CACHE_H
