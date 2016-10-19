#ifndef SERVER_GLOBAL_H
#define SERVER_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(SERVER_LIBRARY)
#  define SERVER_EXPORT Q_DECL_EXPORT
#else
#  define SERVER_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(serverLog)

#endif // SERVER_GLOBAL_H
