

#ifndef STATIStICSPLUGIN_H
#define STATIStICSPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "statistics_global.h"

namespace Statistics {

namespace Internal {

class StatisticsMode;

using namespace ExtensionSystem;

class StatisticsPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "statistics.json")

public:
    StatisticsPlugin();
    ~StatisticsPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    StatisticsMode *m_statisticsMode;
};

} // namespace Internal
} // namespace Statistics

#endif // STATIStICSPLUGIN_H
