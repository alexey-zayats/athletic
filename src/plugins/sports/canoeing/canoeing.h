

#ifndef CANOEINGPLUGIN_H
#define CANOEINGPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "canoeing_global.h"

namespace Canoeing {

namespace Internal {

class CanoeingSport;

using namespace ExtensionSystem;

class CanoeingPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "canoeing.json")

public:
    CanoeingPlugin();
    ~CanoeingPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    CanoeingSport *m_canoeingSport;
};

} // namespace Internal
} // namespace Canoeing

#endif // CANOEINGPLUGIN_H
