
#include "boxing.h"
#include "boxingsport.h"

#include <extensionsystem/pluginmanager.h>

using namespace ExtensionSystem;

using namespace Boxing;
using namespace Boxing::Internal;

Q_LOGGING_CATEGORY(boxingLog, "athletic.plugins.boxing")

BoxingPlugin::BoxingPlugin() :
    m_boxingSport(0)
{
}

BoxingPlugin::~BoxingPlugin()
{
}

bool BoxingPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_boxingSport = new BoxingSport();
    PluginManager::addObject (m_boxingSport);

    return true;
}

void BoxingPlugin::extensionsInitialized()
{
}

bool BoxingPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag BoxingPlugin::aboutToShutdown()
{
    if (m_boxingSport) {
        PluginManager::removeObject (m_boxingSport);
        delete m_boxingSport;
        m_boxingSport = 0;
    }
    return SynchronousShutdown;
}
