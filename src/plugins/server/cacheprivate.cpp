#include "cacheprivate.h"

#include <extensionsystem/pluginmanager.h>

#include <QCoreApplication>
#include <QDebug>
#include <QPluginLoader>
#include <QStringList>

namespace Server
{
    CacheBackend::Factory* Cache::Private::m_backendFactory(NULL);

    Cache::Private::Private(const QString& cacheName)
    {
        if(!m_backendFactory)
        {
            loadBackendFactory();
        }
        backend = m_backendFactory->createCacheBackend(cacheName);
    }

    void Cache::Private::loadBackendFactory()
    {
        QList<Server::CacheBackend::Factory*> cacheFactories = ExtensionSystem::PluginManager::getObjects<Server::CacheBackend::Factory>();
        Q_FOREACH(Server::CacheBackend::Factory* factory, cacheFactories)
        {
            if(factory && factory->loadSettings())
            {
                m_backendFactory = factory;
                break;
            }
        }
        Q_ASSERT(m_backendFactory);
    }

    Cache::Private::~Private()
    {
    }
};
