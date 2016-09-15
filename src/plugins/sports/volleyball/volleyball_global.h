#ifndef VOLLEYBALL_GLOBAL_H
#define VOLLEYBALL_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(VOLLEYBALL_LIBRARY)
#  define VOLLEYBALL_EXPORT Q_DECL_EXPORT
#else
#  define VOLLEYBALL_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(volleyballLog)

#endif // VOLLEYBALL_GLOBAL_H
