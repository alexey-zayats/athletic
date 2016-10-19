#ifndef RAMCACHE_GLOBAL_H
#define RAMCACHE_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(RAMCACHE_LIBRARY)
#  define RAMCACHE_EXPORT Q_DECL_EXPORT
#else
#  define RAMCACHE_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(ramcacheLog)

#endif // RAMCACHE_GLOBAL_H

