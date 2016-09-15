#ifndef VOLLEYBALL_GPLUGIN_H
#define VOLLEYBALL_GPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "volleyball_global.h"

namespace Volleyball {

namespace Internal {

class VolleyballSport;

using namespace ExtensionSystem;

class VolleyballPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "volleyball.json")

public:
    VolleyballPlugin();
    ~VolleyballPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    VolleyballSport *m_volleyballSport;
};

} // namespace Internal
} // namespace Volleyball

#endif // VOLLEYBALL_GPLUGIN_H
