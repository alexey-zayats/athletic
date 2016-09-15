
#include "judo.h"
#include "judosport.h"

#include <extensionsystem/pluginmanager.h>

using namespace ExtensionSystem;
using namespace Judo;
using namespace Judo::Internal;

Q_LOGGING_CATEGORY(judoLog, "athletic.plugins.judo")

JudoPlugin::JudoPlugin() :
    m_judoSport(0)
{
}

JudoPlugin::~JudoPlugin()
{
}

bool JudoPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_judoSport = new JudoSport();
    PluginManager::addObject (m_judoSport);

    return true;
}

void JudoPlugin::extensionsInitialized()
{
}

bool JudoPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag JudoPlugin::aboutToShutdown()
{
    if ( m_judoSport ) {
        PluginManager::removeObject (m_judoSport);
        delete m_judoSport;
        m_judoSport = 0;
    }
    return SynchronousShutdown;
}
