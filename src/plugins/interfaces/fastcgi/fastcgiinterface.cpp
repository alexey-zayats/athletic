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
        if(supported.testFlag(SocketServer::TcpSocket)) stringOutput << QLatin1String("FCGI");
        return stringOutput;
    }

    QStringList Interface::detectedBackends() const
    {
        QStringList out;
        if(SocketServer::activeSocketTypes() & SocketServer::TcpSocket)
        {
            out << QLatin1String("FCGI");
        }
        return out;
    }

    void Interface::configureHttpd(const QString& backend)
    {
        QTextStream cin(stdin);
        QTextStream cout(stdout);

        QSettings *settings = ExtensionSystem::PluginManager::settings ();

        if(backend.toUpper() == QLatin1String("FCGI") )
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
            settings->setValue(QLatin1String("Server/FastCGI/portNumber"), portNumber);
            return;
        }
        qFatal("Unknown FastCGI backend: %s", qPrintable(backend));
    }

    bool Interface::startBackend(const QString& backend)
    {
        quint16 port = 0;

        QSettings *settings = ExtensionSystem::PluginManager::settings ();
        if(backend == QLatin1String("FCGI") )
        {
            port = settings->value( QLatin1String("Server/FastCGI/portNumber") , 0).value<quint16>();
            QTextStream cout(stdout);
            cout << "Following configuration in '" << settings->fileName() << "' and listening for FastCGI on TCP port " << port << endl;
        }

        return m_socketServer->listen(SocketServer::TcpSocket, port);
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
