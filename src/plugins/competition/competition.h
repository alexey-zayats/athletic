

#ifndef COMPETITIONPLUGIN_H
#define COMPETITIONPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "competition_global.h"

namespace Competition {

namespace Internal {

class CompetitionMode;

using namespace ExtensionSystem;

class CompetitionPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "competition.json")

public:
    CompetitionPlugin();
    ~CompetitionPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    CompetitionMode *m_competitionMode;
};

} // namespace Internal
} // namespace Competition

#endif // COMPETITIONPLUGIN_H
