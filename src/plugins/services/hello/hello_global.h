#ifndef HELLO_GLOBAL_H
#define HELLO_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(HELLO_LIBRARY)
#  define HELLO_EXPORT Q_DECL_EXPORT
#else
#  define HELLO_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(helloLog)

#endif // HELLO_GLOBAL_H

