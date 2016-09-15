#ifndef ATHLETE_GLOBAL_H
#define ATHLETE_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(ATHLETE_LIBRARY)
#  define ATHLETE_EXPORT Q_DECL_EXPORT
#else
#  define ATHLETE_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(athleteLog)

#endif // ATHLETE_GLOBAL_H
