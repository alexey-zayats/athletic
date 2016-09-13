#ifndef SCHEDULE_GLOBAL_H
#define SCHEDULE_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(SCHEDULE_LIBRARY)
#  define SCHEDULE_EXPORT Q_DECL_EXPORT
#else
#  define SCHEDULE_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(fightControlLog)

#endif // SCHEDULE_GLOBAL_H
