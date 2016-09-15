#ifndef TENNIS_GLOBAL_H
#define TENNIS_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(TENNIS_LIBRARY)
#  define TENNIS_EXPORT Q_DECL_EXPORT
#else
#  define TENNIS_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(tennisLog)

#endif // TENNIS_GLOBAL_H
