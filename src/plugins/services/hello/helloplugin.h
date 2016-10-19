#ifndef HELLOPLUGIN_H
#define HELLOPLUGIN_H

#include <extensionsystem/iplugin.h>
#include <server/prespawnedspawner.h>

#include "hello_global.h"

namespace Hello {

class ServicePrefix;

namespace Internal {

using namespace ExtensionSystem;

class Plugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.srv.plugin" FILE "hello.json")

public:
    Plugin();
    ~Plugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    ServicePrefix *m_service;
};

} // namespace Internal
} // namespace HelloPlugin

#endif // HELLOPLUGIN_H
