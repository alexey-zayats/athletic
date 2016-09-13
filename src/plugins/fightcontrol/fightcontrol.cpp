
#include "fightcontrol.h"
#include "fightcontrolmode.h"

#include <coreplugin/modemanager.h>

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

    m_fightControlMode = new FightControlMode;
    addAutoReleasedObject(m_fightControlMode);

    return true;
}

void FightControlPLugin::extensionsInitialized()
{
    m_fightControlMode->initPlugins();
}

bool FightControlPLugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag FightControlPLugin::aboutToShutdown()
{
    return SynchronousShutdown;
}
