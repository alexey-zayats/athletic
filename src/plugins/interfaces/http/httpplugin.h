#ifndef HTTPPLUGIN_H
#define HTTPPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "http_global.h"

namespace Http {

class Interface;

namespace Internal {

using namespace ExtensionSystem;

class HTTP_EXPORT HttpPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.srv.plugin" FILE "http.json")

public:
    HttpPlugin();
    ~HttpPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    Interface *m_iface;
};

} // namespace Internal
} // namespace Http

#endif // HTTPPLUGIN_H
