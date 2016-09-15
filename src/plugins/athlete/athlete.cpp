
#include "athlete.h"
#include "athletemode.h"

using namespace Athlete;
using namespace Athlete::Internal;

Q_LOGGING_CATEGORY(athleteLog, "athletic.plugins.athlete")

AthletePlugin::AthletePlugin() :
    m_athleteMode(0)
{
}

AthletePlugin::~AthletePlugin()
{
}

bool AthletePlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_athleteMode = new AthleteMode;
    addAutoReleasedObject (m_athleteMode);

    return true;
}

void AthletePlugin::extensionsInitialized()
{
    m_athleteMode->initPlugins();
}

bool AthletePlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag AthletePlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}
