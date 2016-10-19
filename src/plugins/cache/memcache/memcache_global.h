#ifndef MEMCACHE_GLOBAL_H
#define MEMCACHE_GLOBAL_H

#include <QLoggingCategory>
#include <qglobal.h>

#if defined(MEMCACHE_LIBRARY)
#  define MEMCACHE_EXPORT Q_DECL_EXPORT
#else
#  define MEMCACHE_EXPORT Q_DECL_IMPORT
#endif

Q_DECLARE_LOGGING_CATEGORY(memcacheLog)

#endif // MEMCACHE_GLOBAL_H

