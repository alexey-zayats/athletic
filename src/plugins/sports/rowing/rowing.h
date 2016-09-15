

#ifndef ROWINGPLUGIN_H
#define ROWINGPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "rowing_global.h"

namespace Rowing {

namespace Internal {

class RowingSport;

using namespace ExtensionSystem;

class RowingPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "rowing.json")

public:
    RowingPlugin();
    ~RowingPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    RowingSport *m_rowingSport;
};

} // namespace Internal
} // namespace Rowing

#endif // ROWINGPLUGIN_H
