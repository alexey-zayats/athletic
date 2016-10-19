
#ifndef MatchPlugin_H
#define MatchPlugin_H

#include <extensionsystem/iplugin.h>

#include "match_global.h"

QT_BEGIN_NAMESPACE
class QMenu;
class QMainWindow;
QT_END_NAMESPACE

namespace Match {

namespace Internal {

class MatchMode;

using namespace ExtensionSystem;

class MatchPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "match.json")

public:
    MatchPlugin();
    ~MatchPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:
private:
    MatchMode *m_matchMode;
};

} // namespace Internal
} // namespace Match

#endif // MatchPlugin_H
