#ifndef RAM_CACHE_H
#define RAM_CACHE_H

#include <server/cachebackend.h>

#include <QCache>
#include <QHash>
#include <QObject>
#include <QReadWriteLock>

namespace Ram
{
    ///@internal @brief QCache-based CacheBackend implemntation.
    class Cache : public Server::CacheBackend
    {
        public:
            Cache(const QString& cacheName);
            virtual void remove(const QString& key);
            virtual Server::CacheEntry value(const QString& key) const;
            virtual void setValue(const QString& key, const Server::CacheEntry& entry);
            virtual QReadWriteLock* readWriteLock() const;
            static void setMaxSize(int size);
        private:
            const QString m_keyPrefix;
            static QCache<QString, Server::CacheEntry> m_cache;
            static QReadWriteLock m_lock;
    };

    class CacheFactory : public QObject, public Server::CacheBackend::Factory
    {
        Q_OBJECT
        Q_INTERFACES(Server::CacheBackend::Factory)
        public:
            virtual bool loadSettings();
            virtual Server::CacheBackend* createCacheBackend(const QString& cacheName) const;
    };
}

#endif
