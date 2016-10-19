#ifndef DATABASE_GUARD_H
#define DATABASE_GUARD_H

#include <QSqlDatabase>

namespace Server
{
    class DatabaseGuard
    {
        public:
            DatabaseGuard(const QString& connectionName);
            ~DatabaseGuard();
        private:
            const QString m_database;
    };
}

#endif
