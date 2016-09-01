#ifndef FIGHTCONTROL_GLOBAL_H
#define FIGHTCONTROL_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(FIGHTCONTROL_LIBRARY)
#  define FIGHTCONTROL_EXPORT Q_DECL_EXPORT
#else
#  define FIGHTCONTROL_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(fightControlLog)

#endif // FIGHTCONTROL_GLOBAL_H
