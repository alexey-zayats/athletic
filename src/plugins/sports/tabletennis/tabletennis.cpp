
#include "tabletennis.h"
#include "tabletennissport.h"

#include <extensionsystem/pluginmanager.h>

using namespace ExtensionSystem;

using namespace TableTennis;
using namespace TableTennis::Internal;

Q_LOGGING_CATEGORY(tabletennisLog, "athletic.plugins.tabletennis")

TableTennisPlugin::TableTennisPlugin() :
    m_tableTennisSport(0)
{
}

TableTennisPlugin::~TableTennisPlugin()
{
}

bool TableTennisPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_tableTennisSport = new TableTennisSport();
    PluginManager::addObject (m_tableTennisSport);

    return true;
}

void TableTennisPlugin::extensionsInitialized()
{
}

bool TableTennisPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag TableTennisPlugin::aboutToShutdown()
{
    if (m_tableTennisSport) {
        PluginManager::removeObject (m_tableTennisSport);
        delete m_tableTennisSport;
        m_tableTennisSport = 0;
    }
    return SynchronousShutdown;
}
