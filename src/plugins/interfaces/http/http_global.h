#ifndef HTTP_GLOBAL_H
#define HTTP_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(HTTP_LIBRARY)
#  define HTTP_EXPORT Q_DECL_EXPORT
#else
#  define HTTP_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(httpLog)

#endif // HTTP_GLOBAL_H
