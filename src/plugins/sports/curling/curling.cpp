
#include "curling.h"
#include "curlingsport.h"

#include <extensionsystem/pluginmanager.h>

using namespace ExtensionSystem;

using namespace Curling;
using namespace Curling::Internal;

Q_LOGGING_CATEGORY(curlingLog, "athletic.plugins.curling")

CurlingPlugin::CurlingPlugin() :
    m_curlingSport(0)
{
}

CurlingPlugin::~CurlingPlugin()
{
}

bool CurlingPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_curlingSport = new CurlingSport();
    PluginManager::addObject (m_curlingSport);

    return true;
}

void CurlingPlugin::extensionsInitialized()
{
}

bool CurlingPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag CurlingPlugin::aboutToShutdown()
{
    if ( m_curlingSport ) {
        PluginManager::removeObject (m_curlingSport);
        delete m_curlingSport;
        m_curlingSport = 0;
    }
    return SynchronousShutdown;
}
