#include "helloplugin.h"
#include "helloserviceprefix.h"

#include <extensionsystem/pluginmanager.h>

Q_LOGGING_CATEGORY(helloLog, "athletic.plugins.ramcache")

using namespace Hello;
using namespace Hello::Internal;

Plugin::Plugin() :
    m_service(0)
{
}

Plugin::~Plugin()
{
    if ( 0 != m_service ) {
        ExtensionSystem::PluginManager::removeObject(m_service);
        delete m_service;
        m_service = 0;
    }
}

bool Plugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_service = new ServicePrefix();
    ExtensionSystem::PluginManager::addObject(m_service);

    return true;
}

void Plugin::extensionsInitialized()
{
}

bool Plugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag Plugin::aboutToShutdown()
{
    return SynchronousShutdown;
}

