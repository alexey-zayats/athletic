

#ifndef BOXINGPLUGIN_H
#define BOXINGPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "boxing_global.h"

namespace Boxing {

namespace Internal {

class BoxingSport;

using namespace ExtensionSystem;

class BoxingPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "boxing.json")

public:
    BoxingPlugin();
    ~BoxingPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    BoxingSport *m_boxingSport;
};

} // namespace Internal
} // namespace Boxing

#endif // BOXINGPLUGIN_H
