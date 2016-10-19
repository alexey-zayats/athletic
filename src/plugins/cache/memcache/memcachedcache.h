#ifndef MEMCACHED_CACHE_H
#define MEMCACHED_CACHE_H

#include <server/cachebackend.h>

#include <QReadWriteLock>
#include <QList>

struct memcached_st;

namespace Memcache
{
    /** @internal Cache backend implemented using memcached.
     *
     * Binary key format:
     * 	UTF8 string
     * Binary data format:
     * 	little-endian 64-bit UTC timestamp, data
     *
     * @ingroup plugins
     */
    class Cache : public Server::CacheBackend
    {
        public:
            Cache(const QString& cacheName);
            ~Cache();
            virtual void remove(const QString& key);
            virtual Server::CacheEntry value(const QString& key) const;
            virtual void setValue(const QString& key, const Server::CacheEntry& entry);
            virtual QReadWriteLock* readWriteLock() const;

            class Server
            {
                public:
                    Server(const QString& host, unsigned int port);
                    QString host() const;
                    unsigned int port() const;
                private:
                    QString m_host;
                    unsigned int m_port;
            };
            static void setServers(const QList<Server>& servers);
        private:
            QByteArray fullKey(const QString& key) const;
            memcached_st* m_memcached;
            const QString m_keyPrefix;
            static QList<Server> m_servers;
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
