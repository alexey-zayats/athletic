
#include "rowing.h"
#include "rowingsport.h"

#include <extensionsystem/pluginmanager.h>

using namespace Rowing;
using namespace Rowing::Internal;

using namespace ExtensionSystem;

Q_LOGGING_CATEGORY(rowingLog, "athletic.plugins.rowing")

RowingPlugin::RowingPlugin() :
    m_rowingSport(0)
{
}

RowingPlugin::~RowingPlugin()
{
}

bool RowingPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_rowingSport = new RowingSport;
    PluginManager::addObject (m_rowingSport);

    return true;
}

void RowingPlugin::extensionsInitialized()
{
}

bool RowingPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag RowingPlugin::aboutToShutdown()
{
    if ( m_rowingSport ) {
        ExtensionSystem::PluginManager::removeObject (m_rowingSport);
        delete m_rowingSport;
        m_rowingSport = 0;
    }
    return SynchronousShutdown;
}
