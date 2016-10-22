#include "manager_private.h"

#include "communicationinterface.h"

#include <extensionsystem/pluginmanager.h>

#include <QCoreApplication>
#include <QDebug>
#include <QFileSystemWatcher>
#include <QPluginLoader>
#include <QStringList>
#include <QTextStream>
#include <QSettings>
#include <QSqlDatabase>

namespace Server
{
    Manager::Private::Private(QObject* parent)
        :
            QObject(parent),
            m_applicationWatcher(new QFileSystemWatcher(this)),
            m_caches(new Caches()),
            m_interface(0)
    {
        settings = ExtensionSystem::PluginManager::settings();
        m_interfaces = ExtensionSystem::PluginManager::getObjects<CommunicationInterface>();

        if(QCoreApplication::arguments().contains( QLatin1String("--configure") ))
        {
            configureHttpd();
            configureDatabase();
            exit(0);
        }
        if(QCoreApplication::arguments().contains( QLatin1String("--configure-httpd") ))
        {
            configureHttpd();
            exit(0);
        }
        if(QCoreApplication::arguments().contains( QLatin1String("--configure-database") ))
        {
            configureDatabase();
            exit(0);
        }

        const QString interface = settings->value( QLatin1String("Server/socketType"), QString()).toString();

        QTextStream cerr(stderr);

        if(interface.isEmpty())
        {
            CommunicationInterface* autoInterface = 0;
            QString autoBackend;
            // Auto-detect
            Q_FOREACH(CommunicationInterface *iface, m_interfaces)
            {
                m_interface = iface;
                const QStringList detectedBackends = m_interface->detectedBackends();
                // Preferred - indicated by the environment
                if(!detectedBackends.isEmpty())
                {
                    Q_ASSERT(detectedBackends.count() == 1);
                    const QString detectedBackend = detectedBackends.first();
                    connect(
                        m_interface,
                        SIGNAL(newRequest(Server::Request*)),
                        this,
                        SIGNAL(newRequest(Server::Request*))
                    );
                    if(m_interface->start(detectedBackend))
                    {
                        delete autoInterface;
                        autoInterface = 0;
                        autoBackend.clear();
                        break;
                    }
                    else
                    {
                        cerr << "Failed to initialize auto-detected backend '" << detectedBackend << "' - try --configure-httpd." << endl;
                        exit(1);
                        return;
                    }
                }
                // Available, but not preferred
                const QStringList backends = m_interface->backends();
                Q_FOREACH(const QString& backend, backends)
                {
                    if(!m_interface->requiresConfiguration(backend))
                    {
                        delete autoInterface;
                        autoInterface = m_interface;
                        autoBackend = backend;
                        m_interface = 0;
                        break;
                    }
                }

                m_interface = 0;
            }
            if(autoInterface && ! m_interface)
            {
                m_interface = autoInterface;
                connect(
                    m_interface,
                    SIGNAL(newRequest(Server::Request*)),
                    this,
                    SIGNAL(newRequest(Server::Request*))
                );
                if(!m_interface->start(autoBackend))
                {
                    cerr << "Failed to initialize zero-conf backend '" << autoBackend << "' - try --configure-httpd." << endl;
                    exit(1);
                    return;
                }
            }
            else
            {
                delete autoInterface;
            }
        }
        else
        {
            Q_FOREACH(CommunicationInterface* iface, m_interfaces)
            {
                m_interface = iface;
                if(m_interface && m_interface->backends().contains(interface))
                {
                    connect(
                        m_interface,
                        SIGNAL(newRequest(Server::Request*)),
                        this,
                        SIGNAL(newRequest(Server::Request*))
                    );
                    break;
                }
                else
                {
                    m_interface = 0;
                }
            }

            if(!(m_interface && m_interface->start(interface)))
            {
                // Not a FastCGI application
                if(!m_interface)
                {
                    cerr << "Could not find an implementation for backend " << interface <<endl;
                }
                else
                {
                    cerr << "Failed to initialize backend " << interface << endl;
                }
                cerr << "Perhaps you wanted --configure-httpd?" << endl;
                exit(1);
                return;
            }
        }
        if(!m_interface)
        {
            cerr << "Failed to find a backend." << endl;
            exit(1);
            return;
        }

        connect(
            m_applicationWatcher,
            SIGNAL(fileChanged(QString)),
            this,
            SLOT(shutdown())
        );
        m_applicationWatcher->addPath(QCoreApplication::applicationFilePath());
    }

    Manager::Private::~Private()
    {
        delete m_caches;
    }

    void Manager::Private::shutdown()
    {
        m_interface = 0;
    }

    void Manager::Private::configureHttpd()
    {
        QTextStream cin(stdin);
        QTextStream cout(stdout);

        settings->beginGroup( QLatin1String("Server") );

        QStringList availableInterfaces;
        Q_FOREACH(CommunicationInterface* iface, m_interfaces)
        {
            availableInterfaces.append(iface->backends());
        }
        qSort(availableInterfaces);

        cout << "*****************************************" << endl;
        cout << "***** Server HTTPD Configuration *****" << endl;
        cout << "*****************************************" << endl;
        cout << "The following interfaces are available:" << endl;
        Q_FOREACH(const QString& interface, availableInterfaces)
        {
            cout << " - " << interface << endl;
        }
        cout << "Interface [FCGI]: " << flush;

        QString interface;
        interface = cin.readLine().toUpper();
        if(interface.isEmpty())
        {
            interface = QLatin1String("FCGI");
        }
        settings->setValue( QLatin1String("socketType"), interface);
        Q_FOREACH(CommunicationInterface* iface, m_interfaces)
        {
            m_interface = iface;
            if(m_interface && m_interface->backends().contains(interface)) {
                m_interface->configureHttpd(interface);
                break;
            } else {
                m_interface = 0;
            }
        }

        if(!m_interface){
            qFatal("Not a valid communication method: '%s'", qPrintable(interface));
            return;
        }
        settings->sync();
    }

    void Manager::Private::configureDatabase()
    {
        QTextStream cin(stdin);
        QTextStream cout(stdout);
        QString driver;
        QString host;
        QString name;
        QString user;
        QString password;
        cout << "********************************************" << endl;
        cout << "***** Server Database Configuration *****" << endl;
        cout << "********************************************" << endl;

        QStringList drivers =  QSqlDatabase::drivers();
        cout << "The following drivers are available:" << endl;
        Q_FOREACH(const QString& drv, drivers)
        {
            cout << " - " << drv << endl;
        }

        cout << "Driver [QPSQL]: " << flush;
        driver = cin.readLine();
        if(driver.isEmpty())
        {
            driver = QLatin1String("QPSQL");
        }

        cout << "Host [localhost]: " << flush;
        host = cin.readLine();
        if(host.isEmpty())
        {
            host = QLatin1String("localhost");
        }

        cout << "Database: " << flush;
        name = cin.readLine();

        cout << "User: " << flush;
        user = cin.readLine();

        cout << "Password: " << flush;
        password = cin.readLine();

        settings->beginGroup( QLatin1String("database") );
        settings->setValue( QLatin1String("driver"), driver);
        settings->setValue( QLatin1String("host"), host);
        settings->setValue( QLatin1String("name"), name);
        settings->setValue( QLatin1String("user"), user);
        settings->setValue( QLatin1String("password"), password);
        settings->endGroup();
        settings->sync();

        cout << "Settings saved in " << settings->fileName() << endl;
    }
}
