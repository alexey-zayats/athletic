
#include "competition.h"
#include "competitionmode.h"

using namespace Competition;
using namespace Competition::Internal;

Q_LOGGING_CATEGORY(competitionLog, "athletic.plugins.competition")

CompetitionPlugin::CompetitionPlugin() :
    m_competitionMode(0)
{
}

CompetitionPlugin::~CompetitionPlugin()
{
}

bool CompetitionPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_competitionMode = new CompetitionMode();
    addAutoReleasedObject(m_competitionMode);
    return true;
}

void CompetitionPlugin::extensionsInitialized()
{
}

bool CompetitionPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag CompetitionPlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}
