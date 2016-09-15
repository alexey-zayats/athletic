#ifndef HANDBALL_PLUGIN_H
#define HANDBALL_PLUGIN_H

#include <extensionsystem/iplugin.h>

#include "handball_global.h"

namespace Handball {

namespace Internal {

class HandballSport;

using namespace ExtensionSystem;

class HandballPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "handball.json")

public:
    HandballPlugin();
    ~HandballPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    HandballSport *m_handballSport;
};

} // namespace Internal
} // namespace Handball

#endif // HANDBALL_PLUGIN_H
