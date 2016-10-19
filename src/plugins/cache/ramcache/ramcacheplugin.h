#ifndef RAMCACHEPLUGIN_H
#define RAMCACHEPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "ramcache_global.h"

namespace Ram {

class CacheFactory;

namespace Internal {

using namespace ExtensionSystem;

class RamCachePlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.srv.plugin" FILE "ramcache.json")

public:
    RamCachePlugin();
    ~RamCachePlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    CacheFactory *m_factory;
};

} // namespace Internal
} // namespace RamCachePlugin

#endif // RAMCACHEPLUGIN_H
