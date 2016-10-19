#ifndef HELLO_SERVICE_H
#define HELLO_SERVICE_H

#include <server/service.h>

namespace Hello
{

class Service : public Server::Service
{
    Q_OBJECT
public:
    Service( QObject *parent = 0);
public slots:
    void index();
protected:
    Server::Service::UrlMap urlMap() const;
};

}

#endif // HELLO_SERVICE_H
