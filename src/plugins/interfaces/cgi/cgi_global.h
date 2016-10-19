#ifndef CGI_GLOBAL_H
#define CGI_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(CGI_LIBRARY)
#  define CGI_EXPORT Q_DECL_EXPORT
#else
#  define CGI_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(cgiLog)

#endif // CGI_GLOBAL_H
