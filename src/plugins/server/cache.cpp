#include "cache.h"
#include "cacheprivate.h"

namespace Server
{
    Cache::Cache(const QString& cacheName)
    : d(new Private(cacheName))
    {
    }


    Cache::~Cache()
    {
    }

    void Cache::remove(const QString& key)
    {
        d->backend->remove(key);
    }

    CacheEntry Cache::value(const QString& key) const
    {
        return d->backend->value(key);
    }

    void Cache::setValue(const QString& key, const CacheEntry& entry)
    {
        d->backend->setValue(key, entry);
    }

    QReadWriteLock* Cache::readWriteLock() const
    {
        return d->backend->readWriteLock();
    }
}
