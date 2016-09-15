#ifndef MATCH_GLOBAL_H
#define MATCH_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(MATCH_LIBRARY)
#  define MATCH_EXPORT Q_DECL_EXPORT
#else
#  define MATCH_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(matchLog)

#endif // MATCH_GLOBAL_H
