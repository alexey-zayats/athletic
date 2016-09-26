

#ifndef WRESTLINGPLUGIN_H
#define WRESTLINGPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "wrestling_global.h"

namespace Wrestling {

class MatchBoard;
class MatchControl;

namespace Internal {

class WrestlingSport;

using namespace ExtensionSystem;

class WrestlingPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "wrestling.json")

public:
    WrestlingPlugin();
    ~WrestlingPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    WrestlingSport *m_wrestlingSport;
    MatchBoard *m_matchBoard;
    MatchControl *m_matchControl;
};

} // namespace Internal
} // namespace Wrestling

#endif // WRESTLINGPLUGIN_H
