
#ifndef FIGHTCONTROLPLUGIN_H
#define FIGHTCONTROLPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "fightcontrol_global.h"

QT_BEGIN_NAMESPACE
class QMenu;
class QMainWindow;
QT_END_NAMESPACE

namespace FightControl {

namespace Internal {

using namespace ExtensionSystem;

class FightControlPLugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "FightControl.json")

public:
    FightControlPLugin();
    ~FightControlPLugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:
private:
};

} // namespace Internal
} // namespace FightControl

#endif // FIGHTCONTROLPLUGIN_H
