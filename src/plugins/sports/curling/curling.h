

#ifndef CURLINGPLUGIN_H
#define CURLINGPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "curling_global.h"

namespace Curling {

namespace Internal {

class CurlingSport;

using namespace ExtensionSystem;

class CurlingPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "curling.json")

public:
    CurlingPlugin();
    ~CurlingPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    CurlingSport *m_curlingSport;
};

} // namespace Internal
} // namespace Curling

#endif // CURLINGPLUGIN_H
