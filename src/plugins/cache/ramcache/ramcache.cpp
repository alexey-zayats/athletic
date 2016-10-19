#include "ramcache.h"

#include <extensionsystem/pluginmanager.h>

#include <QCoreApplication>
#include <QDebug>
#include <QReadLocker>
#include <QStringList>
#include <QWriteLocker>
#include <QSettings>

namespace Ram
{
    QCache<QString, Server::CacheEntry> Cache::m_cache(0);
    QReadWriteLock Cache::m_lock(QReadWriteLock::Recursive);

    Cache::Cache(const QString& cacheName)
        :
            m_keyPrefix(cacheName + QLatin1String("::") )
    {
    }

    Server::CacheBackend* CacheFactory::createCacheBackend(const QString& cacheName) const
    {
        return new Cache(cacheName);
    }

    bool CacheFactory::loadSettings()
    {
        QSettings *settings = ExtensionSystem::PluginManager::settings ();
        if(settings->value( QLatin1String("cache/backend"), QLatin1String("RamCache") ) == QLatin1String("RamCache") )
        {
            Cache::setMaxSize(settings->value(QLatin1String("RamCache/maxSize"), 10 * 1024 * 1024).toInt());
            return true;
        }
        return false;
    }

    void Cache::setMaxSize(int size)
    {
        m_cache.setMaxCost(size);
    }

    Server::CacheEntry Cache::value(const QString& key) const
    {
        QReadLocker lock(&m_lock);
        Server::CacheEntry* pointer = m_cache.object(m_keyPrefix + key);
        if(pointer)
        {
            return Server::CacheEntry(*pointer);
        }
        else
        {
            return Server::CacheEntry();
        }
    }

    QReadWriteLock* Cache::readWriteLock() const
    {
        return &m_lock;
    }

    void Cache::setValue(const QString& key, const Server::CacheEntry& entry)
    {
        QWriteLocker lock(&m_lock);
        m_cache.insert(m_keyPrefix + key, new Server::CacheEntry(entry), entry.data().length());
    }

    void Cache::remove(const QString& key)
    {
        QWriteLocker lock(&m_lock);
        m_cache.remove(m_keyPrefix + key);
    }
}

