#include "fastcgiinterface.h"

#include "fastcgisocketmanager.h"
#include "socketserver.h"
#include "fastcgi.h"

#include <extensionsystem/pluginmanager.h>

#include <QSettings>

namespace FastCgi
{
    Interface::Interface(QObject* parent)
    : CommunicationInterface(parent)
    , m_socketServer(new SocketServer(this))
    {
        connect(
            m_socketServer,
            SIGNAL(newConnection()),
            this,
            SLOT(acceptNewConnection())
        );
    }

    QStringList Interface::backends() const
    {
        QStringList stringOutput;
        SocketServer::SocketTypes supported = SocketServer::supportedSocketTypes();
        if(supported.testFlag(SocketServer::UnixSocket)) stringOutput << QLatin1String("FCGI-UNIX");
        if(supported.testFlag(SocketServer::TcpSocket)) stringOutput << QLatin1String("FCGI-TCP");
        return stringOutput;
    }

    QStringList Interface::detectedBackends() const
    {
        QStringList out;
        if(SocketServer::activeSocketTypes() & SocketServer::UnixSocket)
        {
            out << QLatin1String("FCGI-UNIX");
        }
        return out;
    }

    void Interface::configureHttpd(const QString& backend)
    {
        QTextStream cin(stdin);
        QTextStream cout(stdout);

        QSettings *settings = ExtensionSystem::PluginManager::settings ();

        if(backend.toUpper() == QLatin1String("FCGI-UNIX") )
        {
            return;
        }
        if(backend.toUpper() == QLatin1String("FCGI-TCP") )
        {
            settings->beginGroup( QLatin1String("FastCGI") );
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
            settings->setValue(QLatin1String("portNumber"), portNumber);
            settings->endGroup ();
            return;
        }
        qFatal("Unknown FastCGI backend: %s", qPrintable(backend));
    }

    bool Interface::startBackend(const QString& backend)
    {
        quint16 port = 0;
        SocketServer::SocketType socketType;

        if(backend == QLatin1String("FCGI-UNIX") )
        {
            socketType = SocketServer::UnixSocket;
        }

        QSettings *settings = ExtensionSystem::PluginManager::settings ();
        if(backend == QLatin1String("FCGI-TCP") )
        {
            port = settings->value( QLatin1String("FastCGI/portNumber") , 0).value<quint16>();
            QTextStream cout(stdout);
            socketType = SocketServer::TcpSocket;

            cout << "Following configuration in '" << settings->fileName() << "' and listening for FastCGI on TCP port " << port << endl;
        }

        return m_socketServer->listen(socketType, port);
    }

    Interface::~Interface()
    {
    }

    bool Interface::isFinished() const
    {
        return m_socketServer->isFinished();
    }

    void Interface::acceptNewConnection()
    {
        /* We're connected, setup a SocketManager.
         * This will delete itself when appropriate (via deleteLater())
         */
        SocketManager* socket = new SocketManager(m_socketServer->nextPendingConnection(), 0);
        addWorker(socket);
    }
}
