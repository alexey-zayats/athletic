#include "httpplugin.h"
#include "httpinterface.h"

#include <extensionsystem/pluginmanager.h>

using namespace Http;
using namespace Http::Internal;

Q_LOGGING_CATEGORY(cgiLog, "athletic.plugins.http")

HttpPlugin::HttpPlugin() :
    m_iface(0)
{
}

HttpPlugin::~HttpPlugin()
{
    if ( 0 != m_iface) {
        PluginManager::removeObject (m_iface);
        delete m_iface;
        m_iface = 0;
    }
}

bool HttpPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_iface= new Interface(this);
    PluginManager::addObject (m_iface);

    return true;
}

void HttpPlugin::extensionsInitialized()
{
}

bool HttpPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag HttpPlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}
