#ifndef UPDATER_GLOBAL_H
#define UPDATER_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(UPDATER_LIBRARY)
#  define UPDATER_EXPORT Q_DECL_EXPORT
#else
#  define UPDATER_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(updaterLog)

#endif // UPDATER_GLOBAL_H
