#ifndef DATABASE_PRIVATE_H
#define DATABASE_PRIVATE_H

#include "databaseguard.h"

#include <QAtomicInt>
#include <QThreadStorage>

class QThread;

namespace Server
{
    class DatabasePrivate
    {
        public:
            static QSqlDatabase database(bool open = true);
            static QSqlDatabase addDatabase(const QString& type);
            static bool haveConnection();
        private:
            static void removeConnection();
            static QString connectionName();
            static int threadId();

            static QAtomicInt m_maxThreadId;
            static QThreadStorage<int*> m_threadIds;
            static QThreadStorage<DatabaseGuard*> m_databases;
    };
}

#endif // DATABASE_PRIVATE_H
