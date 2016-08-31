
#ifndef COREPLUGIN_H
#define COREPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "core_global.h"

QT_BEGIN_NAMESPACE
class QMenu;
class QMainWindow;
QT_END_NAMESPACE


namespace Utils {
class Theme;
}

namespace Core {

namespace Internal {

using namespace ExtensionSystem;

class CorePlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "Core.json")

public:
    CorePlugin();
    ~CorePlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    void initStyle();
    QMainWindow *mainWindow;
};

} // namespace Internal
} // namespace Core

#endif // COREPLUGIN_H
