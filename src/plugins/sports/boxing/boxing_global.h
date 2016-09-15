#ifndef BOXING_GLOBAL_H
#define BOXING_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(BOXING_LIBRARY)
#  define BOXING_EXPORT Q_DECL_EXPORT
#else
#  define BOXING_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(boxingLog)

#endif // BOXING_GLOBAL_H
