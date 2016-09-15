
#include "match.h"
#include "matchmode.h"

#include <coreplugin/modemanager.h>

using namespace Match;
using namespace Match::Internal;

Q_LOGGING_CATEGORY(matchLod, "athletic.plugins.match")

MatchPLugin::MatchPLugin()
{
}

MatchPLugin::~MatchPLugin()
{
}

bool MatchPLugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_matchMode = new MatchMode();
    addAutoReleasedObject(m_matchMode);

    return true;
}

void MatchPLugin::extensionsInitialized()
{
    m_matchMode->initPlugins();
}

bool MatchPLugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag MatchPLugin::aboutToShutdown()
{
    return SynchronousShutdown;
}
