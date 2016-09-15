#ifndef HANDBALL_GLOBAL_H
#define HANDBALL_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(HANDBALL_LIBRARY)
#  define HANDBALL_EXPORT Q_DECL_EXPORT
#else
#  define HANDBALL_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(handballLog)

#endif // HANDBALL_GLOBAL_H
