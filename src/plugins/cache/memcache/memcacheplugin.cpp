#include "memcacheplugin.h"
#include "memcachedcache.h"

#include <extensionsystem/pluginmanager.h>

Q_LOGGING_CATEGORY(memcacheLod, "athletic.plugins.memcache")

using namespace Memcache;
using namespace Memcache::Internal;

MemcachePlugin::MemcachePlugin() :
    m_factory(0)
{
    qDebug() << Q_FUNC_INFO;
}

MemcachePlugin::~MemcachePlugin()
{
    qDebug() << Q_FUNC_INFO;
    if ( 0 != m_factory ) {
        ExtensionSystem::PluginManager::removeObject(m_factory);
        delete m_factory;
        m_factory = 0;
    }
}

bool MemcachePlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    qDebug() << Q_FUNC_INFO;
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_factory = new CacheFactory();
    ExtensionSystem::PluginManager::addObject(m_factory);

    return true;
}

void MemcachePlugin::extensionsInitialized()
{
    qDebug() << Q_FUNC_INFO;
}

bool MemcachePlugin::delayedInitialize()
{
    qDebug() << Q_FUNC_INFO;
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag MemcachePlugin::aboutToShutdown()
{
    qDebug() << Q_FUNC_INFO;
    return SynchronousShutdown;
}

