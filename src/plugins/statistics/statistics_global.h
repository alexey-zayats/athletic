#ifndef STATISTICS_GLOBAL_H
#define STATISTICS_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(STATISTICS_LIBRARY)
#  define STATISTICS_EXPORT Q_DECL_EXPORT
#else
#  define STATISTICS_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(statisticsLog)

#endif // STATISTICS_GLOBAL_H
