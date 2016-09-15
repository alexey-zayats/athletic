#ifndef CURLING_GLOBAL_H
#define CURLING_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(CURLING_LIBRARY)
#  define CURLING_EXPORT Q_DECL_EXPORT
#else
#  define CURLING_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(curlingLog)

#endif // CURLING_GLOBAL_H
