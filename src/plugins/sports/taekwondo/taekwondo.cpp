
#include "taekwondo.h"
#include "taekwondosport.h"

#include <extensionsystem/pluginmanager.h>

using namespace ExtensionSystem;
using namespace Taekwondo;
using namespace Taekwondo::Internal;

Q_LOGGING_CATEGORY(taekwondoLog, "athletic.plugins.taekwondo")

TaekwondoPlugin::TaekwondoPlugin() :
    m_taekwondoSport(0)
{
}

TaekwondoPlugin::~TaekwondoPlugin()
{
}

bool TaekwondoPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_taekwondoSport = new TaekwondoSport();
    ExtensionSystem::PluginManager::addObject (m_taekwondoSport);
    return true;
}

void TaekwondoPlugin::extensionsInitialized()
{
}

bool TaekwondoPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag TaekwondoPlugin::aboutToShutdown()
{
    if ( m_taekwondoSport ) {
        ExtensionSystem::PluginManager::removeObject (m_taekwondoSport);
        delete m_taekwondoSport;
        m_taekwondoSport = 0;
    }
    return SynchronousShutdown;
}
