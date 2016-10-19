#include "databaseguard.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QThread>

namespace Server
{
    DatabaseGuard::DatabaseGuard(const QString& connectionName)
        : m_database(connectionName)
    {
    }

    DatabaseGuard::~DatabaseGuard()
    {
        qDebug() << "Shutting down database connection in thread" << QThread::currentThread();
        QSqlDatabase::removeDatabase(m_database);
    }
};
