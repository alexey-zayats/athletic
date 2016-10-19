#ifndef SCGIPLUGIN_H
#define SCGIPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "scgi_global.h"

namespace Scgi {

class Interface;

namespace Internal {

using namespace ExtensionSystem;

class SCGI_EXPORT Plugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.srv.plugin" FILE "scgi.json")

public:
    Plugin();
    ~Plugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    Interface *m_iface;
};

} // namespace Internal
} // namespace Scgi

#endif // SCGIPLUGIN_H
