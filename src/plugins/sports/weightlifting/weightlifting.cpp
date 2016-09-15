
#include "weightlifting.h"
#include "weightliftingsport.h"

#include <extensionsystem/pluginmanager.h>

using namespace ExtensionSystem;

using namespace WeightLifting;
using namespace WeightLifting::Internal;

Q_LOGGING_CATEGORY(weightliftingLog, "athletic.plugins.boxing")

WeightLiftingPlugin::WeightLiftingPlugin() :
    m_weightLiftingSport(0)
{
}

WeightLiftingPlugin::~WeightLiftingPlugin()
{
}

bool WeightLiftingPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_weightLiftingSport = new WeightLiftingSport();
    PluginManager::addObject (m_weightLiftingSport);

    return true;
}

void WeightLiftingPlugin::extensionsInitialized()
{
}

bool WeightLiftingPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag WeightLiftingPlugin::aboutToShutdown()
{
    if (m_weightLiftingSport) {
        PluginManager::removeObject (m_weightLiftingSport);
        delete m_weightLiftingSport;
        m_weightLiftingSport = 0;
    }
    return SynchronousShutdown;
}
