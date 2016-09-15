
#include "canoeing.h"
#include "canoeingsport.h"

#include <extensionsystem/pluginmanager.h>

using namespace ExtensionSystem;

using namespace Canoeing;
using namespace Canoeing::Internal;

Q_LOGGING_CATEGORY(canoeingLog, "athletic.plugins.canoeing")

CanoeingPlugin::CanoeingPlugin() :
    m_canoeingSport(0)
{
}

CanoeingPlugin::~CanoeingPlugin()
{
}

bool CanoeingPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_canoeingSport = new CanoeingSport();
    PluginManager::addObject (m_canoeingSport);

    return true;
}

void CanoeingPlugin::extensionsInitialized()
{
}

bool CanoeingPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag CanoeingPlugin::aboutToShutdown()
{
    if (m_canoeingSport) {
        PluginManager::removeObject (m_canoeingSport);
        delete m_canoeingSport;
        m_canoeingSport = 0;
    }
    return SynchronousShutdown;
}
