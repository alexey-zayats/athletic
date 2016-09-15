
#include "wrestling.h"
#include "wrestlingsport.h"

#include <extensionsystem/pluginmanager.h>

using namespace Wrestling;
using namespace Wrestling::Internal;

Q_LOGGING_CATEGORY(wrestlingLog, "athletic.plugins.wrestling")

WrestlingPlugin::WrestlingPlugin() :
    m_wrestlingSport(0)
{
}

WrestlingPlugin::~WrestlingPlugin()
{
}

bool WrestlingPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_wrestlingSport = new WrestlingSport();
    ExtensionSystem::PluginManager::addObject (m_wrestlingSport);
    return true;
}

void WrestlingPlugin::extensionsInitialized()
{
}

bool WrestlingPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag WrestlingPlugin::aboutToShutdown()
{
    if ( m_wrestlingSport ) {
        ExtensionSystem::PluginManager::removeObject (m_wrestlingSport);
        delete m_wrestlingSport;
        m_wrestlingSport = 0;
    }
    return SynchronousShutdown;
}
