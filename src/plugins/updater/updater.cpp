
#include "updater.h"

using namespace Updater;
using namespace Updater::Internal;

Q_LOGGING_CATEGORY(updaterLog, "athletic.plugins.updater")

UpdaterPlugin::UpdaterPlugin()
{
}

UpdaterPlugin::~UpdaterPlugin()
{
}

bool UpdaterPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    return true;
}

void UpdaterPlugin::extensionsInitialized()
{
}

bool UpdaterPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag UpdaterPlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}
