#include "helloservice.h"

#include <server/request.h>

#include <QTextStream>

namespace Hello
{

Service::Service(QObject *parent) :
    Server::Service(parent)
{
}

void Service::index()
{
    QTextStream out(request());
    out << "Index goes here";
}

Server::Service::UrlMap Service::urlMap() const
{
    Server::Service::UrlMap map;
    map.append( QLatin1String(""), SLOT(index()));
    return map;
}

}
