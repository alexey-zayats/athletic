#include "memcachedcache.h"

#include <libmemcached/memcached.h>
#include <extensionsystem/pluginmanager.h>

#include <QtEndian>
#include <QCoreApplication>
#include <QDebug>
#include <QReadLocker>
#include <QStringList>
#include <QWriteLocker>
#include <QSettings>

namespace Memcache
{
    QReadWriteLock Cache::m_lock(QReadWriteLock::Recursive);
    QList<Cache::Server> Cache::m_servers;

    Cache::Cache(const QString& cacheName)
        :
            m_memcached(memcached_create(NULL)),
            m_keyPrefix(QCoreApplication::organizationDomain() + QLatin1Char('/')
                        + QCoreApplication::applicationName() + QLatin1Char('/')
                        + cacheName + QLatin1Char('/') )
    {
        memcached_return rt;

        Q_FOREACH(const Server& server, m_servers)
        {
            rt = memcached_server_add(m_memcached, server.host().toLatin1().constData(), server.port());
            if(rt != MEMCACHED_SUCCESS)
            {
                qFatal("Failed to add memcached server %s:%d.", qPrintable(server.host()), server.port());
            }
        }
    }

    QByteArray Cache::fullKey(const QString& key) const
    {
        return QString(m_keyPrefix + key).toUtf8();
    }

    Cache::~Cache()
    {
        memcached_free(m_memcached);
    }

    void Cache::setServers(const QList<Server>& servers)
    {
        m_servers = servers;
    }

    Cache::Server::Server(const QString& host, unsigned int port)
        :
            m_host(host),
            m_port(port)
    {
    }

    QString Cache::Server::host() const
    {
        return m_host;
    }

    unsigned int Cache::Server::port() const
    {
        return m_port;
    }

    Server::CacheBackend *CacheFactory::createCacheBackend(const QString& cacheName) const
    {
        return new Cache(cacheName);
    }

    bool CacheFactory::loadSettings()
    {
        QSettings *settings = ExtensionSystem::PluginManager::settings();
        if(settings->value( QLatin1String("cache/backend") ) == QLatin1String("MemcachedCache") )
        {
            QList<Cache::Server> servers;
            const int size = settings->beginReadArray( QLatin1String("MemcachedServers") );
            if(size == 0)
            {
                servers.append(Cache::Server( QLatin1String("localhost"), MEMCACHED_DEFAULT_PORT));
            }
            else
            {
                for(int i = 0; i < size; ++i)
                {
                    settings->setArrayIndex(i);
                    const QString host(settings->value( QLatin1String("host") ).toString());
                    if(!host.isNull())
                    {
                        const unsigned int port = settings->value( QLatin1String("port"), MEMCACHED_DEFAULT_PORT).value<unsigned int>();
                        servers.append(Cache::Server(host, port));
                    }
                }
            }
            settings->endArray();
            Cache::setServers(servers);
            return true;
        }
        return false;
    }

    Server::CacheEntry Cache::value(const QString& key) const
    {
        QReadLocker lock(&m_lock);

        const QByteArray rawKey(fullKey(key));

        char* rawData;
        size_t rawDataLength;
        uint32_t flags;
        memcached_return rt;

        rawData = memcached_get(
            m_memcached,
            rawKey.constData(),
            rawKey.length(),
            &rawDataLength,
            &flags,
            &rt
        );

        if(rt != MEMCACHED_SUCCESS && rt != MEMCACHED_NOTFOUND)
        {
            qFatal("Memcached error: %s", memcached_strerror(m_memcached, rt));
        }

        Q_ASSERT(rawDataLength >= sizeof(quint64) || !rawData);
        if(rawDataLength < sizeof(quint64) || !rawData)
        {
            return ::Server::CacheEntry();
        }

        const quint64 timeStamp = qFromLittleEndian(*reinterpret_cast<quint64*>(rawData));
        const QByteArray data(rawData + sizeof(quint64), rawDataLength - sizeof(quint64));
        return ::Server::CacheEntry(QDateTime::fromTime_t(timeStamp), data);
    }

    QReadWriteLock* Cache::readWriteLock() const
    {
        return &m_lock;
    }

    void Cache::setValue(const QString& key, const ::Server::CacheEntry& entry)
    {
        QWriteLocker lock(&m_lock);

        // Binary key
        const QByteArray rawKey(fullKey(key));

        // Binary data
        const quint64 dateTime(qToLittleEndian(static_cast<quint64>(entry.timeStamp().toTime_t())));
        QByteArray rawData(reinterpret_cast<const char*>(&dateTime), sizeof(quint64));
        rawData.append(entry.data());

        // Store in memcached
        memcached_return rt;
        rt = memcached_set(
            m_memcached,
            rawKey.constData(),
            rawKey.length(),
            rawData.constData(),
            rawData.length(),
            0, // expire
            0 // flags
        );
        if(rt != MEMCACHED_SUCCESS)
        {
            qFatal("Memcached error: %s", memcached_strerror(m_memcached, rt));
        }
    }

    void Cache::remove(const QString& key)
    {
        QWriteLocker lock(&m_lock);
        const QByteArray rawKey(fullKey(key));
        const memcached_return rt = memcached_delete(
            m_memcached,
            rawKey.constData(),
            rawKey.length(),
            0
        );
        if(rt != MEMCACHED_SUCCESS)
        {
            qFatal("Memcached error: %s", memcached_strerror(m_memcached, rt));
        }
    }
}
