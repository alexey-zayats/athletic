

#ifndef UPDATERPLUGIN_H
#define UPDATERPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "updater_global.h"

namespace Updater {

namespace Internal {

using namespace ExtensionSystem;

class UpdaterPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "Updater.json")

public:
    UpdaterPlugin();
    ~UpdaterPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:

};

} // namespace Internal
} // namespace Updater

#endif // UPDATERPLUGIN_H
