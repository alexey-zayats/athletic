
#include "handball.h"
#include "handballsport.h"

#include <extensionsystem/pluginmanager.h>

using namespace ExtensionSystem;

using namespace Handball;
using namespace Handball::Internal;

Q_LOGGING_CATEGORY(handballLog, "athletic.plugins.handball")

HandballPlugin::HandballPlugin() :
    m_handballSport(0)
{
}

HandballPlugin::~HandballPlugin()
{
}

bool HandballPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_handballSport = new HandballSport();
    PluginManager::addObject (m_handballSport);

    return true;
}

void HandballPlugin::extensionsInitialized()
{
}

bool HandballPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag HandballPlugin::aboutToShutdown()
{
    if (m_handballSport) {
        PluginManager::removeObject (m_handballSport);
        delete m_handballSport;
        m_handballSport = 0;
    }
    return SynchronousShutdown;
}
