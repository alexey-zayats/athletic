#include "helloservice.h"

#include <QTextStream>

namespace Hello
{

Service::Service(QObject *parent) :
    Server::Service(parent)
{
}

bool caseInsensitiveLessThan(const QByteArray &s1, const QByteArray &s2)
{
    return s1.toLower() < s2.toLower();
}

QString Service::printData(Server::DataSource ds)
{
    QString outString;
    QTextStream out(&outString);
    QHash<QByteArray, QByteArray> data = request()->rawValues(ds);

    QList<QByteArray> keys = data.keys();
    qSort(keys.begin(), keys.end(), caseInsensitiveLessThan);

    Q_FOREACH(QByteArray key, keys) {
         out << "<b>" << key << "</b>: " <<  data.value(key) << "<br/>\n";
    }

    return outString;
}

void Service::index()
{
    QTextStream out(request());
    out << "<h1>Index goes here</h1>\n";

    out << "<hr/><b>Get data</b><br/>\n";
    out << printData(Server::GetData);

    out << "<hr/><b>Post data</b><br/>\n";
    out << printData(Server::PostData);

    out << "<hr/><b>Server data</b><br/>\n";
    out << printData(Server::ServerData);
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
