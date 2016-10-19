#include "fastcgiplugin.h"
#include "fastcgiinterface.h"

#include <extensionsystem/pluginmanager.h>

using namespace FastCgi;
using namespace FastCgi::Internal;

Q_LOGGING_CATEGORY(fastCgiLog, "athletic.plugins.fastcgi")

FastCgiPlugin::FastCgiPlugin() :
    m_iface(0)
{
}

FastCgiPlugin::~FastCgiPlugin()
{
    if ( 0 != m_iface) {
        PluginManager::removeObject (m_iface);
        delete m_iface;
        m_iface = 0;
    }
}

bool FastCgiPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_iface = new Interface(this);
    PluginManager::addObject (m_iface);

    return true;
}

void FastCgiPlugin::extensionsInitialized()
{
}

bool FastCgiPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag FastCgiPlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}
