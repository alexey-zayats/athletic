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

void Service::article(QString id)
{
    QTextStream out(request());
    out << "Requested hello data by id "  << id;
}

Server::Service::UrlMap Service::urlMap() const
{
    Server::Service::UrlMap map;
    map.append( QLatin1String(""), SLOT(index()));
    map.append( QLatin1String("(\\d+)"), SLOT(article(QString)));
    return map;
}

}
