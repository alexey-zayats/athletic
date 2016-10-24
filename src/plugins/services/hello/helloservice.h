#ifndef HELLO_SERVICE_H
#define HELLO_SERVICE_H

#include <server/service.h>
#include <server/request.h>

namespace Hello
{

class Service : public Server::Service
{
    Q_OBJECT
public:
    Service( QObject *parent = 0);
public slots:
    void index();
    void article(QString
                 );
protected:
    Server::Service::UrlMap urlMap() const;
private:
    QString printData(Server::DataSource ds);
};

}

#endif // HELLO_SERVICE_H
