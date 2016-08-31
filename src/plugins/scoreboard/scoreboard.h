
#ifndef SCOREBOARDPLUGIN_H
#define SCOREBOARDPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "scoreboard_global.h"

QT_BEGIN_NAMESPACE
class QMenu;
class QMainWindow;
QT_END_NAMESPACE

namespace Scoreboard {

namespace Internal {

using namespace ExtensionSystem;

class ScoreboardPLugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "Scoreboard.json")

public:
    ScoreboardPLugin();
    ~ScoreboardPLugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:
private:
};

} // namespace Internal
} // namespace Scoreboard

#endif // SCOREBOARDPLUGIN_H
