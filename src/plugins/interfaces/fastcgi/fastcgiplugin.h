#ifndef FASTCGIPLUGIN_H
#define FASTCGIPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "fastcgi_global.h"

namespace FastCgi {

class Interface;

namespace Internal {

using namespace ExtensionSystem;

class FASTCGI_EXPORT FastCgiPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.srv.plugin" FILE "fastcgi.json")

public:
    FastCgiPlugin();
    ~FastCgiPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    Interface *m_iface;
};

} // namespace Internal
} // namespace FastCgi

#endif // FASTCGIPLUGIN_H
