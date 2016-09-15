#ifndef ROWING_GLOBAL_H
#define ROWING_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(ROWING_LIBRARY)
#  define ROWING_EXPORT Q_DECL_EXPORT
#else
#  define ROWING_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(rowingLog)

#endif // ROWING_GLOBAL_H
