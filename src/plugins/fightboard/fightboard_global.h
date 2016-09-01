#ifndef FIGHTBOARD_GLOBAL_H
#define FIGHTBOARD_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(FIGHTBOARD_LIBRARY)
#  define FIGHTBOARD_EXPORT Q_DECL_EXPORT
#else
#  define FIGHTBOARD_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(fightBoardLog)

#endif // FIGHTBOARD_GLOBAL_H
