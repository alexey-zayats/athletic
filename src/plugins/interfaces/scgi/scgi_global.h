#ifndef SCGI_GLOBAL_H
#define SCGI_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(SCGI_LIBRARY)
#  define SCGI_EXPORT Q_DECL_EXPORT
#else
#  define SCGI_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(scgiLog)

#endif // SCGI_GLOBAL_H
