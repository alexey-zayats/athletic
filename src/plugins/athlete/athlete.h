

#ifndef ATHLETEPLUGIN_H
#define ATHLETEPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "athlete_global.h"

namespace Athlete {

namespace Internal {

class AthleteMode;

using namespace ExtensionSystem;

class AthletePlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "athlete.json")

public:
    AthletePlugin();
    ~AthletePlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    AthleteMode *m_athleteMode;
};

} // namespace Internal
} // namespace Athlete

#endif // ATHLETEPLUGIN_H
