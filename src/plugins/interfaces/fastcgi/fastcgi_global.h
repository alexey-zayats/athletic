#ifndef FASTCGI_GLOBAL_H
#define FASTCGI_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(FASTCGI_LIBRARY)
#  define FASTCGI_EXPORT Q_DECL_EXPORT
#else
#  define FASTCGI_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(fastCgiLog)

#endif // FASTCGI_GLOBAL_H
