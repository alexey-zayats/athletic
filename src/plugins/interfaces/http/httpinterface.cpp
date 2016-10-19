#include "httpinterface.h"
#include "httprequest.h"

#include <extensionsystem/pluginmanager.h>

#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QMutex>
#include <QMutexLocker>
#include <QStringList>
#include <QTcpServer>
#include <QTextStream>
#include <QSettings>

namespace Http
{
    Interface::Interface(QObject* parent)
        : Server::CommunicationInterface(parent)
    , m_server(new QTcpServer(this))
    {
        connect(
            m_server,
            SIGNAL(newConnection()),
            SLOT(startResponse())
        );
    }

    QStringList Interface::backends() const
    {
        return QStringList() << QLatin1String("HTTP");
    }

    bool Interface::requiresConfiguration(const QString& backend) const
    {
        Q_ASSERT(backend == QLatin1String("HTTP") );
        Q_UNUSED(backend);
        return false;
    }

    void Interface::configureHttpd(const QString& backend)
    {
        QTextStream cin(stdin);
        QTextStream cout(stdout);
        QSettings *settings = ExtensionSystem::PluginManager::settings ();

        if(backend.toUpper() == QLatin1String("HTTP") )
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
            settings->beginGroup( QLatin1String("HTTP") );
            settings->setValue(QLatin1String("portNumber"), portNumber);
            cout << "Optionally, you can specify a path relative to the current directory, where Server will serve static content. This may be horribly insecure." << endl;
            cout << "Static content directory [none]: " << flush;
            const QString directory = cin.readLine().trimmed();
            if(directory.isEmpty())
            {
                settings->remove( QLatin1String("staticDirectory") );
            }
            else
            {
                settings->setValue( QLatin1String("staticDirectory"), QDir::cleanPath(directory));
            }
            settings->endGroup();
            return;
        }
        qFatal("Unknown HTTP backend: %s", qPrintable(backend));
    }

    bool Interface::startBackend(const QString& backend)
    {
        if(backend != QLatin1String("HTTP") )
        {
            return false;
        }

        QSettings *settings = ExtensionSystem::PluginManager::settings ();
        settings->beginGroup( QLatin1String("Server") );

        const quint16 portNumber = settings->value(QLatin1String("HTTP/portNumber"), 0).value<quint16>();
        m_staticDirectory = settings->value(QLatin1String("HTTP/staticDirectory"), QString()).toString();

        settings->endGroup();

        QTextStream cout(stdout);
        if(!m_staticDirectory.isEmpty())
        {
            cout << "***WARNING*** Serving static content from ./" << m_staticDirectory << "/" << " (" << QFileInfo(m_staticDirectory).canonicalFilePath() << ")" << endl;
            cout << "Do *NOT* use this inefficient and insecure feature in a production setting, or any other environment" << endl;
            cout << "where untrusted users have access to this webserver." << endl;
        }
        if(!m_server->listen(QHostAddress::Any, portNumber))
        {
            qFatal("Failed to listen on port %d: %s", portNumber, qPrintable(m_server->errorString()));
        }
        if(portNumber != 0)
        {
            cout << "Using configuration in " << settings->fileName() << ", and running an HTTP server on port " << portNumber << endl;
        }
        else
        {
            cout << "Auto-configured HTTP server running on port " << m_server->serverPort() << " - if this isn't what you want, re-run with --configure-httpd" << endl;
        }
        return true;
    }

    void Interface::startResponse()
    {
        static Server::ClientIODevice::HeaderMap standardHeaders;
        static QStringList staticDirectories;
        static QMutex mutex;
        {
            QMutexLocker lock(&mutex);
            if(standardHeaders.isEmpty())
            {
                standardHeaders.insert("SERVER_SOFTWARE", "Server/HttpPlugin");
                standardHeaders.insert("SERVER_PORT", QString::number(m_server->serverPort()).toLatin1());
                standardHeaders.insert("GATEWAY_INTERFACE", "CGI/1.1");
                if(!m_staticDirectory.isEmpty())
                {
                    staticDirectories.append(QFileInfo(m_staticDirectory).canonicalFilePath());
                }
            }
        }
        connect(
            new Request(standardHeaders,
                        Server::ClientIODevice::HeaderMap(),
                        staticDirectories,
                        m_server->nextPendingConnection(),
                        this),
            SIGNAL(gotHeaders(Request*)),
            SLOT(announceRequest(Request*))
        );
    }

    void Interface::announceRequest(Request* request)
    {
        addRequest(request);
    }

    Interface::~Interface()
    {
    }

    bool Interface::isFinished() const
    {
        // "isFinished" means "thread load is zero; are you going to get any requests?"; answer is 'maybe'
        return false;
    }
}
