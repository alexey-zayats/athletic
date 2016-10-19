#include "scgiinterface.h"
#include "scgirequest.h"

#include <extensionsystem/pluginmanager.h>

#include <QStringList>
#include <QTextStream>
#include <QTcpServer>
#include <QSettings>

namespace Scgi
{
    Interface::Interface(QObject* parent)
        : Server::CommunicationInterface(parent)
    , m_tcpServer(0)
    {
    }

    QStringList Interface::backends() const
    {
        return QStringList() << QLatin1String("SCGI-TCP");
    }

    void Interface::spawnRequest()
    {
        addWorker(new Request(m_tcpServer->nextPendingConnection(), NULL));
    }

    void Interface::configureHttpd(const QString& backend)
    {
        QTextStream cin(stdin);
        QTextStream cout(stdout);

        QSettings *settings = ExtensionSystem::PluginManager::settings ();

        if(backend.toUpper() == QLatin1String("SCGI-TCP") )
        {
            QString portString;
            cout << "Port number: " << flush;
            portString = cin.readLine();
            bool ok;
            quint32 portNumber = portString.toUInt(&ok);
            if(!(ok && portNumber))
            {
                qFatal("Not a valid port number.");
                return;
            }
            settings->beginGroup( QLatin1String("SCGI") );
            settings->setValue( QLatin1String("portNumber"), portNumber);
            settings->endGroup ();
            return;
        }
        qFatal("Unknown SCGI backend: %s", qPrintable(backend));
    }

    bool Interface::startBackend(const QString& backend)
    {
        if(backend != QLatin1String("SCGI-TCP") )
        {
            return false;
        }
        QSettings *settings = ExtensionSystem::PluginManager::settings ();
        const quint16 portNumber = settings->value(QLatin1String("SCGI/portNumber"), 0).value<quint16>();
        if(portNumber == 0)
        {
            return false;
        }

        m_tcpServer = new QTcpServer(this);
        if(!m_tcpServer->listen(QHostAddress::Any, portNumber))
        {
            qFatal("SCGI: Failed to listen on TCP port %d: %s", portNumber, qPrintable(m_tcpServer->errorString()));
            return false;
        }

        QTextStream cout(stdout);
        cout << "Following configuration in '" << settings->fileName() << "' and listening for SCGI on TCP port " << portNumber << endl;

        connect(
            m_tcpServer,
            SIGNAL(newConnection()),
            SLOT(spawnRequest())
        );

        return true;
    }

    Interface::~Interface()
    {
        shutdown();
    }

    void Interface::shutdown()
    {
        if(m_tcpServer)
        {
            m_tcpServer->close();
        }
    }

    bool Interface::isFinished() const
    {
        // "isFinished" means "thread load is zero; are you going to get any requests?"; answer is 'maybe'
        return false;
    }
}
