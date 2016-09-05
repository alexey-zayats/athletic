
#include "fightboard.h"

using namespace FightBoard;
using namespace FightBoard::Internal;

Q_LOGGING_CATEGORY(fightBoardLog, "athletic.plugins.fightboard")

FightBoardPLugin::FightBoardPLugin()
{
}

FightBoardPLugin::~FightBoardPLugin()
{
}

bool FightBoardPLugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);
    return true;
}

void FightBoardPLugin::extensionsInitialized()
{
}

bool FightBoardPLugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag FightBoardPLugin::aboutToShutdown()
{
    return SynchronousShutdown;
}
