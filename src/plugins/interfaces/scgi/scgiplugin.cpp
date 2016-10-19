#include "scgiplugin.h"
#include "scgiinterface.h"

#include <extensionsystem/pluginmanager.h>

using namespace Scgi;
using namespace Scgi::Internal;

Q_LOGGING_CATEGORY(scgiLog, "athletic.plugins.scgi")

Plugin::Plugin() :
    m_iface(0)
{
}

Plugin::~Plugin()
{
    if ( 0 != m_iface) {
        PluginManager::removeObject (m_iface);
        delete m_iface;
        m_iface = 0;
    }
}

bool Plugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_iface = new Interface(this);
    PluginManager::addObject (m_iface);

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
