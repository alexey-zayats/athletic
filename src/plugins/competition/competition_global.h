#ifndef COMPETITION_GLOBAL_H
#define COMPETITION_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(COMPETITION_LIBRARY)
#  define COMPETITION_EXPORT Q_DECL_EXPORT
#else
#  define COMPETITION_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(competitionLog)

#endif // COMPETITION_GLOBAL_H
