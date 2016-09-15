#ifndef JUDO_GLOBAL_H
#define JUDO_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(JUDO_LIBRARY)
#  define JUDO_EXPORT Q_DECL_EXPORT
#else
#  define JUDO_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(judoLog)

#endif // JUDO_GLOBAL_H
