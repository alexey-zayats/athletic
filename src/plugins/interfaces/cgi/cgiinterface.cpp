#include "cgiinterface.h"
#include "cgirequest.h"

#include <QDebug>
#include <QStringList>
#include <QTimer>

#include <cstdlib>

namespace Cgi
{
    Interface::Interface(QObject* parent)
        : Server::CommunicationInterface(parent)
    {
    }

    Interface::~Interface()
    {
    }

    bool Interface::isFinished() const
    {
        return true;
    }

    QStringList Interface::backends() const
    {
        return QStringList() << QLatin1String("CGI");
    }

    QStringList Interface::detectedBackends() const
    {
        if(QLatin1String(getenv("GATEWAY_INTERFACE")) == QLatin1String("CGI/1.1") )
        {
            return QStringList() << QLatin1String("CGI");
        }
        return QStringList();
    }

    void Interface::init()
    {
        addRequest(new Request(this));
    }

    bool Interface::startBackend(const QString& backend)
    {
        Q_ASSERT(backend == QLatin1String("CGI"));
        Q_UNUSED(backend);
        QTimer::singleShot(0, this, SLOT(init()));
        return true;
    }
}
