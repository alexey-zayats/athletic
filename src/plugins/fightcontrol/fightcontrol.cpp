
#include "fightcontrol.h"

using namespace FightControl;
using namespace FightControl::Internal;

Q_LOGGING_CATEGORY(fightControlLog, "athletic.plugins.fightcontrol")

FightControlPLugin::FightControlPLugin()
{
}

FightControlPLugin::~FightControlPLugin()
{
}

bool FightControlPLugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);
    return true;
}

void FightControlPLugin::extensionsInitialized()
{
}

bool FightControlPLugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag FightControlPLugin::aboutToShutdown()
{
    return SynchronousShutdown;
}
