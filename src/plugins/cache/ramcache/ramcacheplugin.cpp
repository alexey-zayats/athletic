#include "ramcacheplugin.h"
#include "ramcache.h"

#include <extensionsystem/pluginmanager.h>

Q_LOGGING_CATEGORY(ramcacheLog, "athletic.plugins.ramcache")

using namespace Ram;
using namespace Ram::Internal;

RamCachePlugin::RamCachePlugin() :
    m_factory(0)
{
}

RamCachePlugin::~RamCachePlugin()
{
    if ( 0 != m_factory ) {
        ExtensionSystem::PluginManager::removeObject(m_factory);
        delete m_factory;
        m_factory = 0;
    }
}

bool RamCachePlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_factory = new CacheFactory();
    ExtensionSystem::PluginManager::addObject(m_factory);
    return true;
}

void RamCachePlugin::extensionsInitialized()
{
}

bool RamCachePlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag RamCachePlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}

