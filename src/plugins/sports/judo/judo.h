

#ifndef JUDOPLUGIN_H
#define JUDOPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "judo_global.h"

namespace Judo {

namespace Internal {

class JudoSport;

using namespace ExtensionSystem;

class JudoPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "judo.json")

public:
    JudoPlugin();
    ~JudoPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    JudoSport *m_judoSport;
};

} // namespace Internal
} // namespace Judo

#endif // JUDOPLUGIN_H
