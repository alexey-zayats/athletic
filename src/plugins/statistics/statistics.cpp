
#include "statistics.h"
#include "statisticsmode.h"

using namespace Statistics;
using namespace Statistics::Internal;

Q_LOGGING_CATEGORY(statisticsLog, "athletic.plugins.statistics")

StatisticsPlugin::StatisticsPlugin()
{
}

StatisticsPlugin::~StatisticsPlugin()
{
}

bool StatisticsPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_statisticsMode = new StatisticsMode;
    addAutoReleasedObject (m_statisticsMode);
    return true;
}

void StatisticsPlugin::extensionsInitialized()
{
    m_statisticsMode->initPlugins ();
}

bool StatisticsPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag StatisticsPlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}
