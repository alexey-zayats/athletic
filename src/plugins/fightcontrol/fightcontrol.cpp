
#include "fightcontrol.h"

using namespace FightControl;
using namespace FightControl::Internal;

Q_LOGGING_CATEGORY(fightControlLog, "athletic.plugins.fightcontrol")

FightControlPLugin::FightControlPLugin()
{
    qCDebug(fightControlLog) << "FightControlPLugin";
}

FightControlPLugin::~FightControlPLugin()
{
    qCDebug(fightControlLog) << "~FightControlPLugin";
}

bool FightControlPLugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);
    qCDebug(fightControlLog) << "initialize";
    return true;
}

void FightControlPLugin::extensionsInitialized()
{
    qCDebug(fightControlLog) << "extensionsInitialized";
}

bool FightControlPLugin::delayedInitialize()
{
    qCDebug(fightControlLog) << "delayedInitialize";
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag FightControlPLugin::aboutToShutdown()
{
    qCDebug(fightControlLog) << "aboutToShutdown";
    return SynchronousShutdown;
}
