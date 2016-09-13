
#ifndef SCHEDULELPLUGIN_H
#define SCHEDULELPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "schedule_global.h"

QT_BEGIN_NAMESPACE
class QMenu;
class QMainWindow;
QT_END_NAMESPACE

namespace Schedule {

namespace Internal {

class ScheduleMode;

using namespace ExtensionSystem;

class SchedulePLugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "schedule.json")

public:
    SchedulePLugin();
    ~SchedulePLugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:
private:
    ScheduleMode *m_scheduleMode;
};

} // namespace Internal
} // namespace FightControl

#endif // SCHEDULELPLUGIN_H
