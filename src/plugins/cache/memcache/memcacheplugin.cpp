#include "memcacheplugin.h"
#include "memcachedcache.h"

#include <extensionsystem/pluginmanager.h>

Q_LOGGING_CATEGORY(memcacheLod, "athletic.plugins.memcache")

using namespace Memcache;
using namespace Memcache::Internal;

MemcachePlugin::MemcachePlugin() :
    m_factory(0)
{
}

MemcachePlugin::~MemcachePlugin()
{
    if ( 0 != m_factory ) {
        ExtensionSystem::PluginManager::removeObject(m_factory);
        delete m_factory;
        m_factory = 0;
    }
}

bool MemcachePlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_factory = new CacheFactory();
    ExtensionSystem::PluginManager::addObject(m_factory);

    return true;
}

void MemcachePlugin::extensionsInitialized()
{
}

bool MemcachePlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag MemcachePlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}

