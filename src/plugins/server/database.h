#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

namespace Server
{
    /** Convenience class for using and cleaning up a single database connection per application.
     *
     * Database connections will be removed and cleaned up when the calling thread exits.
     *
     * @warning This class is not available if WITH_SQL_SUPPORT=OFF is
     * 	passed to CMake when building Server. The default is
     * 	WITH_SQL_SUPPORT=ON.
     */
    class Database
    {
        public:
            /// Whether or not there is an open connection for this thread.
            static bool haveConnection();
            /** Return a database for this thread, if there is one.
             *
             * if @p open is true, the database is opened if it is closed.
             */
            static QSqlDatabase database(bool open = true);
            /** Add a new, per-thread database connection to a database
             * of the specified type.
             */
            static QSqlDatabase addDatabase(const QString& type);
            /** Reads configuration file variables.
             *
             * These can be generated by running your application with --configure-database
             */
            static QSqlDatabase addDatabase();
    };
}

#endif // DATABASE_H
