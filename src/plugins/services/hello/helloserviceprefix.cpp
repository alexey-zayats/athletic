#include "helloserviceprefix.h"
#include "helloservice.h"

namespace Hello
{
ServicePrefix::ServicePrefix() :
    m_spawner(0)
{
    m_spawner = new Server::Spawner<Service>();
}

ServicePrefix::~ServicePrefix()
{
    delete m_spawner;
}

QString ServicePrefix::prefix() const
{
    return QLatin1String("hello");
}

Server::SpawnerBase *ServicePrefix::service()
{
    return m_spawner;
}

}
