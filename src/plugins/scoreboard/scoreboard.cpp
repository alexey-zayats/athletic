
#include "scoreboard.h"

using namespace Scoreboard;
using namespace Scoreboard::Internal;

Q_LOGGING_CATEGORY(scoreBoardLog, "athletic.plugins.scoreboard")

ScoreboardPLugin::ScoreboardPLugin()
{
    qCDebug(scoreBoardLog) << "ScoreboardPLugin";
}

ScoreboardPLugin::~ScoreboardPLugin()
{
    qCDebug(scoreBoardLog) << "~ScoreboardPLugin";
}

bool ScoreboardPLugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);
    qCDebug(scoreBoardLog) << "initialize";
    return true;
}

void ScoreboardPLugin::extensionsInitialized()
{
    qCDebug(scoreBoardLog) << "extensionsInitialized";
}

bool ScoreboardPLugin::delayedInitialize()
{
    qCDebug(scoreBoardLog) << "delayedInitialize";
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag ScoreboardPLugin::aboutToShutdown()
{
    qCDebug(scoreBoardLog) << "aboutToShutdown";
    return SynchronousShutdown;
}
