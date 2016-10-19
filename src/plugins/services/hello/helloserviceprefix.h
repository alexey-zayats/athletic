#ifndef HELLOSERVICEPREFIX_H
#define HELLOSERVICEPREFIX_H

#include <QtCore/QObject>

#include <server/iserviceprefix.h>

namespace Hello
{

class Service;

class ServicePrefix : public Server::IServicePrefix
{
public:
    ServicePrefix();
    ~ServicePrefix();
    QString prefix() const;
    Server::SpawnerBase *service();
private:
    Server::SpawnerBase *m_spawner;
};
}

#endif // HELLOSERVICEPREFIX_H
