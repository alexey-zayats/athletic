#include "serverplugin.h"

#include "manager.h"
#include "prefixmapper.h"
#include "iserviceprefix.h"

#include <extensionsystem/pluginmanager.h>

using namespace Server;
using namespace Server::Internal;

Q_LOGGING_CATEGORY(serverLog, "athletic.plugins.server")

ServerPlugin::ServerPlugin() :
    m_manager(0),
    m_mapper(0)
{
}

ServerPlugin::~ServerPlugin()
{
    delete m_manager;
    delete m_mapper;
}

bool ServerPlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    return true;
}

void ServerPlugin::extensionsInitialized()
{
    m_manager = new Manager(this);
    m_mapper = new PrefixMapper(PrefixMapper::ThreadedResponses, this);
    m_mapper->connect(m_manager, SIGNAL(newRequest(Server::Request*)),SLOT(respond(Server::Request*)));

    QList<Server::IServicePrefix*> serviceList =  ExtensionSystem::PluginManager::getObjects<Server::IServicePrefix>();
    Q_FOREACH(Server::IServicePrefix *service, serviceList) {
        m_mapper->addMapping(service->prefix(), service->service(), SLOT(respond(Server::Request*)));
    }
}

bool ServerPlugin::delayedInitialize()
{
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag ServerPlugin::aboutToShutdown()
{
    return SynchronousShutdown;
}
