
#include "match.h"
#include "matchmode.h"

#include <coreplugin/modemanager.h>

using namespace Match;
using namespace Match::Internal;

Q_LOGGING_CATEGORY(matchLod, "athletic.plugins.match")

MatchPlugin::MatchPlugin()
{
}

MatchPlugin::~MatchPlugin()
{
}

bool MatchPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_matchMode = new MatchMode();
    addAutoReleasedObject(m_matchMode);

    return true;
}

void MatchPlugin::extensionsInitialized()
{
    m_matchMode->initPlugins();
}

bool MatchPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag MatchPlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}
