
#ifndef FIGHTBOARDPLUGIN_H
#define FIGHTBOARDPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "fightboard_global.h"

QT_BEGIN_NAMESPACE
class QMenu;
class QMainWindow;
QT_END_NAMESPACE

namespace FightBoard {

namespace Internal {

using namespace ExtensionSystem;

class FightBoardPLugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "fightboard.json")

public:
    FightBoardPLugin();
    ~FightBoardPLugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:
private:
};

} // namespace Internal
} // namespace FightBoard

#endif // SCOREBOARDPLUGIN_H
