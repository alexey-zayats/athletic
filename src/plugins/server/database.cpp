#include "database.h"
#include "databaseprivate.h"

#include <extensionsystem/pluginmanager.h>

#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>
#include <QThread>
#include <QSettings>

namespace Server
{
    QAtomicInt DatabasePrivate::m_maxThreadId;
    QThreadStorage<int*> DatabasePrivate::m_threadIds;
    QThreadStorage<DatabaseGuard*> DatabasePrivate::m_databases;

    QSqlDatabase Database::database(bool open)
    {
        return DatabasePrivate::database(open);
    }

    QSqlDatabase Database::addDatabase(const QString& type)
    {
        return DatabasePrivate::addDatabase(type);
    }

    QSqlDatabase Database::addDatabase()
    {
        QSettings *settings = ExtensionSystem::PluginManager::settings();
        settings->beginGroup( QLatin1String("database") );
        const QString name = settings->value( QLatin1String("name") ).toString();
        if(name.isEmpty())
        {
            qFatal("In Server::Database::addDatabase(), with no database configuration. Try running the application with --configure-database");
            return QSqlDatabase();
        }

        const QString driver = settings->value( QLatin1String("driver"), QLatin1String("QPSQL")).toString();
        const QString host = settings->value( QLatin1String("host") ).toString();
        const QString user = settings->value( QLatin1String("user") ).toString();
        const QString password = settings->value( QLatin1String("password") ).toString();

        QSqlDatabase database = Database::addDatabase(driver);
        database.setHostName(host);
        database.setUserName(user);
        database.setPassword(password);
        database.setDatabaseName(name);
        if(!database.open())
        {
            qFatal("In Server::Database::addDatabase(), couldn't open database '%s' with configured values (%s). Try re-running --configure-database", qPrintable(name), qPrintable(database.lastError().text()));
            return QSqlDatabase();
        }

        return database;
    }

    bool Database::haveConnection()
    {
        return DatabasePrivate::haveConnection();
    }

    bool DatabasePrivate::haveConnection()
    {
        bool sqlThinksSo = QSqlDatabase::connectionNames().contains(connectionName());
        bool localStorageThinksSo = m_databases.hasLocalData();
        Q_ASSERT(sqlThinksSo == localStorageThinksSo);

        if(!sqlThinksSo)
        {
            // Nothing indicates it's open, it's not
            return false;
        }
        // Just because we /had/ a connection doesn't mean it's still open
        if(!database().isOpen())
        {
            removeConnection();
            return false;
        }
        if(sqlThinksSo)
        {
            QSqlQuery query(database());
            query.exec( QLatin1String("SELECT 1") );
            if(query.lastError().isValid())
            {
                removeConnection();
                return false;
            }
        }
        return true;
    }

    void DatabasePrivate::removeConnection()
    {
        m_databases.setLocalData(NULL);
        Q_ASSERT(!m_databases.hasLocalData());
        QSqlDatabase::removeDatabase(connectionName());
    }

    int DatabasePrivate::threadId()
    {
        int threadId;
        if(!m_threadIds.hasLocalData())
        {
            threadId = m_maxThreadId.fetchAndAddRelease(1);
            m_threadIds.setLocalData(new int(threadId));
        }
        else
        {
            threadId = *m_threadIds.localData();
        }
        return threadId;
    }

    QString DatabasePrivate::connectionName()
    {
        return QString( QLatin1String("Server::Database connection - thread %1") ).arg(threadId());
    }

    QSqlDatabase DatabasePrivate::database(bool open)
    {
        return QSqlDatabase::database(connectionName(), open);
    }

    QSqlDatabase DatabasePrivate::addDatabase(const QString& type)
    {
        if(!m_databases.hasLocalData())
        {
            m_databases.setLocalData(new DatabaseGuard(connectionName()));
        }
        return QSqlDatabase::addDatabase(type, connectionName());
    }
}
