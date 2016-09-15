#ifndef CANOEING_GLOBAL_H
#define CANOEING_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(CANOEING_LIBRARY)
#  define CANOEING_EXPORT Q_DECL_EXPORT
#else
#  define CANOEING_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(canoeingLog)

#endif // CANOEING_GLOBAL_H
