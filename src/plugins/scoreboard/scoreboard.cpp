
#include "scoreboard.h"

using namespace Scoreboard;
using namespace Scoreboard::Internal;

Q_LOGGING_CATEGORY(scoreBoardLog, "athletic.plugins.scoreboard")

ScoreboardPLugin::ScoreboardPLugin()
{
    qCDebug(scoreBoardLog) << Q_FUNC_INFO;
}

ScoreboardPLugin::~ScoreboardPLugin()
{
    qCDebug(scoreBoardLog) << Q_FUNC_INFO;
}

bool ScoreboardPLugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);
    qCDebug(scoreBoardLog) << Q_FUNC_INFO;
    return true;
}

void ScoreboardPLugin::extensionsInitialized()
{
    qCDebug(scoreBoardLog) << Q_FUNC_INFO;
}

bool ScoreboardPLugin::delayedInitialize()
{
    qCDebug(scoreBoardLog) << Q_FUNC_INFO;
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag ScoreboardPLugin::aboutToShutdown()
{
    qCDebug(scoreBoardLog) << Q_FUNC_INFO;
    return SynchronousShutdown;
}
