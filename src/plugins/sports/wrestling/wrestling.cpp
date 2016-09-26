
#include "wrestling.h"
#include "wrestlingsport.h"

#include "matchboard.h"
#include "matchcontrol.h"

#include <extensionsystem/pluginmanager.h>

using namespace Wrestling;
using namespace Wrestling::Internal;

Q_LOGGING_CATEGORY(wrestlingLog, "athletic.plugins.wrestling")

WrestlingPlugin::WrestlingPlugin() :
    m_wrestlingSport(0),
    m_matchBoard(0),
    m_matchControl(0)
{
}

WrestlingPlugin::~WrestlingPlugin()
{
}

bool WrestlingPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    m_wrestlingSport = new WrestlingSport();
    m_matchBoard = new MatchBoard();
    m_matchControl = new MatchControl();

    ExtensionSystem::PluginManager::addObject (m_wrestlingSport);
    ExtensionSystem::PluginManager::addObject (m_matchBoard);
    ExtensionSystem::PluginManager::addObject (m_matchControl);
    return true;
}

void WrestlingPlugin::extensionsInitialized()
{
}

bool WrestlingPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag WrestlingPlugin::aboutToShutdown()
{
    if ( m_wrestlingSport ) {
        ExtensionSystem::PluginManager::removeObject (m_wrestlingSport);
        delete m_wrestlingSport;
        m_wrestlingSport = 0;
    }
    if ( m_matchBoard ) {
        ExtensionSystem::PluginManager::removeObject (m_matchBoard);
        delete m_matchBoard;
        m_matchBoard = 0;
    }
    if ( m_matchControl ) {
        ExtensionSystem::PluginManager::removeObject (m_matchControl);
        delete m_matchControl;
        m_matchControl = 0;
    }
    return SynchronousShutdown;
}
