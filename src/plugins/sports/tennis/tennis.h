#ifndef TENNIS_PLUGIN_H
#define TENNIS_PLUGIN_H

#include <extensionsystem/iplugin.h>

#include "tennis_global.h"

namespace Tennis {

namespace Internal {

class TennisSport;

using namespace ExtensionSystem;

class TennisPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "tennis.json")

public:
    TennisPlugin();
    ~TennisPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    TennisSport *m_tennisSport;
};

} // namespace Internal
} // namespace Tennis

#endif // TENNIS_PLUGIN_H
