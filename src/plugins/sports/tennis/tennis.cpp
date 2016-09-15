
#include "tennis.h"
#include "tennissport.h"

#include <extensionsystem/pluginmanager.h>

using namespace ExtensionSystem;

using namespace Tennis;
using namespace Tennis::Internal;

Q_LOGGING_CATEGORY(tennisLog, "athletic.plugins.tennis")

TennisPlugin::TennisPlugin() :
    m_tennisSport(0)
{
}

TennisPlugin::~TennisPlugin()
{
}

bool TennisPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_tennisSport = new TennisSport();
    PluginManager::addObject (m_tennisSport);

    return true;
}

void TennisPlugin::extensionsInitialized()
{
}

bool TennisPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag TennisPlugin::aboutToShutdown()
{
    if (m_tennisSport) {
        PluginManager::removeObject (m_tennisSport);
        delete m_tennisSport;
        m_tennisSport = 0;
    }
    return SynchronousShutdown;
}
