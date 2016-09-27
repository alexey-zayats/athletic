
#include "schedule.h"
#include "schedulemode.h"

#include <coreplugin/coreconstants.h>
#include <coreplugin/icore.h>
#include <coreplugin/imode.h>
#include <coreplugin/modemanager.h>

#include <utils/hostosinfo.h>

using namespace Schedule;
using namespace Schedule::Internal;

using namespace Core;
using namespace ExtensionSystem;
using namespace Utils;

Q_LOGGING_CATEGORY(scheduleLog, "athletic.plugins.schedule")

SchedulePLugin::SchedulePLugin()
: m_scheduleMode(0)
{
}

SchedulePLugin::~SchedulePLugin()
{
}

bool SchedulePLugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    if (!Utils::HostOsInfo::canCreateOpenGLContext(errorMessage))
        return false;

    m_scheduleMode = new ScheduleMode;
    addAutoReleasedObject(m_scheduleMode);

    return true;
}

void SchedulePLugin::extensionsInitialized()
{
//    m_scheduleMode->initPlugins();
    ModeManager::activateMode(m_scheduleMode->id());
}

bool SchedulePLugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag SchedulePLugin::aboutToShutdown()
{
    return SynchronousShutdown;
}
