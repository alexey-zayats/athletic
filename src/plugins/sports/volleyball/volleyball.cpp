
#include "volleyball.h"
#include "volleyballsport.h"

#include <extensionsystem/pluginmanager.h>

using namespace ExtensionSystem;

using namespace Volleyball;
using namespace Volleyball::Internal;

Q_LOGGING_CATEGORY(volleyballLog, "athletic.plugins.volleyball")

VolleyballPlugin::VolleyballPlugin() :
    m_volleyballSport(0)
{
}

VolleyballPlugin::~VolleyballPlugin()
{
}

bool VolleyballPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_volleyballSport = new VolleyballSport();
    PluginManager::addObject (m_volleyballSport);

    return true;
}

void VolleyballPlugin::extensionsInitialized()
{
}

bool VolleyballPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag VolleyballPlugin::aboutToShutdown()
{
    if (m_volleyballSport) {
        PluginManager::removeObject (m_volleyballSport);
        delete m_volleyballSport;
        m_volleyballSport = 0;
    }
    return SynchronousShutdown;
}
