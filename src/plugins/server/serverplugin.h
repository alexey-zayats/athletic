#ifndef SERVERPLUGIN_H
#define SERVERPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "server_global.h"

namespace Server {

class Manager;
class PrefixMapper;

namespace Internal {

using namespace ExtensionSystem;

class ServerPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.srv.plugin" FILE "server.json")

public:
    ServerPlugin();
    ~ServerPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    Manager *m_manager;
    PrefixMapper *m_mapper;
};

} // namespace Internal
} // namespace Server

#endif // SERVERPLUGIN_H
