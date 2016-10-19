#include "cgiplugin.h"
#include "cgiinterface.h"

#include <extensionsystem/pluginmanager.h>

using namespace Cgi;
using namespace Cgi::Internal;

Q_LOGGING_CATEGORY(cgiLog, "athletic.plugins.cgi")

CgiPlugin::CgiPlugin() :
    m_iface(0)
{
}

CgiPlugin::~CgiPlugin()
{
    if ( 0 != m_iface ) {
        PluginManager::removeObject (m_iface);
        delete m_iface;
        m_iface = 0;
    }
}

bool CgiPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_iface = new Interface(this);
    PluginManager::addObject (m_iface);

    return true;
}

void CgiPlugin::extensionsInitialized()
{
}

bool CgiPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag CgiPlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}
