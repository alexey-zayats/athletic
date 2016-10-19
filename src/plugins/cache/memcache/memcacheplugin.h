#ifndef MEMCACHEPLUGIN_H
#define MEMCACHEPLUGIN_H

#include <extensionsystem/iplugin.h>

#include "memcache_global.h"

namespace Memcache {

class CacheFactory;

namespace Internal {

using namespace ExtensionSystem;

class MemcachePlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.srv.plugin" FILE "memcache.json")

public:
    MemcachePlugin();
    ~MemcachePlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    CacheFactory *m_factory;
};

} // namespace Internal
} // namespace Memcache

#endif // MEMCACHEPLUGIN_H
