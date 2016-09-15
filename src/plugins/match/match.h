
#ifndef MATCHPLUGIN_H
#define MATCHPLUGIN_H

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

class MatchPLugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "match.json")

public:
    MatchPLugin();
    ~MatchPLugin();

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

#endif // MATCHPLUGIN_H
