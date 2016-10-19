#ifndef CGIPLUGIN_H
#define CGIPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "cgi_global.h"

namespace Cgi {

class Interface;

namespace Internal {

using namespace ExtensionSystem;

class CGI_EXPORT CgiPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.srv.plugin" FILE "cgi.json")

public:
    CgiPlugin();
    ~CgiPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    Interface *m_iface;
};

} // namespace Internal
} // namespace Cgi

#endif // CGIPLUGIN_H
