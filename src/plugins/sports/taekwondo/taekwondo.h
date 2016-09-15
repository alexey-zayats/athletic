

#ifndef TAEKWONDOPLUGIN_H
#define TAEKWONDOPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "taekwondo_global.h"

namespace Taekwondo {

namespace Internal {

class TaekwondoSport;

using namespace ExtensionSystem;

class TaekwondoPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "taekwondo.json")

public:
    TaekwondoPlugin();
    ~TaekwondoPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    TaekwondoSport *m_taekwondoSport;
};

} // namespace Internal
} // namespace Taekwondo

#endif // TAEKWONDOPLUGIN_H
