
#include "fightboard.h"

using namespace FightBoard;
using namespace FightBoard::Internal;

Q_LOGGING_CATEGORY(fightBoardLog, "athletic.plugins.fightboard")

FightBoardPLugin::FightBoardPLugin()
{
    qCDebug(fightBoardLog) << "FightBoardPLugin";
}

FightBoardPLugin::~FightBoardPLugin()
{
    qCDebug(fightBoardLog) << "~FightBoardPLugin";
}

bool FightBoardPLugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);
    qCDebug(fightBoardLog) << "initialize";
    return true;
}

void FightBoardPLugin::extensionsInitialized()
{
    qCDebug(fightBoardLog) << "extensionsInitialized";
}

bool FightBoardPLugin::delayedInitialize()
{
    qCDebug(fightBoardLog) << "delayedInitialize";
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag FightBoardPLugin::aboutToShutdown()
{
    qCDebug(fightBoardLog) << "aboutToShutdown";
    return SynchronousShutdown;
}
