#ifndef SERVER_CACHE
#define SERVER_CACHE

#include "cacheentry.h"
#include "server_global.h"

class QReadWriteLock;

namespace Server
{
    /** @brief A read-write-locked cache structure.
     *
     * Depending on the Server configuration, this will use one of
     * several backends; for example, QCache-based, or memcached-based.
     *
     * If QCache is used, the cache will be shared between all threads in
     * the current process. If memcached is used, the cache will:
     * - Perform better (honestly, even though it's out of process)
     * - Be shared with any other instances of the same application using
     *   the same memcached pool.
     *
     * All backends should lock as neccessary, but you may want to lock at
     * an outer scope for performance.
     *
     * Keep in mind that even with a recursive lock, the locks must be of
     * the same type; for example, all the writing calls will deadlock
     * if called while a read lock is open.
     *
     * @section settings Settings
     *
     * @todo A configuration interface for these needs to be added (probably --configure-cache?)
     *
     * In the settings file (.ApplicationName), there are several settings for this:
@verbatim
[cache]
backend={RamCache|MemcachedCache}
@endverbatim
     *
     * RamCache is always available, and gives a cache shared between all requests in the current process.
     * Memcached performs better, and depending on the configuration, can be used by multiple processes,
     * or even multiple machines.
     *
     * @subsection ramcache RamCache
     *
     * RamCache is a simple QCache-backed cache, with just one setting:
     *
@verbatim
[RamCache]
maxSize=numberOfBytes
@endverbatim
     *
     * This allows you to configure the maximum size of the cache
     *
     * @subsection memcached MemcachedCache
     *
     * This backend performs better, can be shared amongst a cluster, but is only available if
     * Server was built with -DWITH_MEMCACHED_SUPPORT=ON
     *
@verbatim
[MemcachedServers]
size=numberOfServers
0/host=foo
0/port=11211
1/host=bar
1/port=11211
...
@endverbatim
     *
     * If a port is not set, Server uses libmemcached's default - normally 11211.
     *
     * If the size is zero, or this section is omitted, Server will try to connect to
     * a memcached server on localhost, on the default port. If this does not work, the
     * application will exit.
     *
     * @ingroup plugins
     */
    class SERVER_EXPORT Cache
    {
        public:
            /// Construct a Cache with the given name.
            Cache(const QString& cacheName);
            /// Destroy a cache.
            ~Cache();

            /// Remove a key from the cache.
            void remove(const QString& key);

            /** Retrieve a value from the cache.
             *
             * If the entry isnt' in the cache, an invalid
             * CacheEntry will be returned.
             */
            CacheEntry value(const QString& key) const;

            /** Set a value in the cache.
             *
             * If a value already exists with the given key, it is
             * overwritten.
             */
            void setValue(const QString& key, const CacheEntry& object);
        protected:
            /// Return a pointer to the QReadWriteLock.
            QReadWriteLock* readWriteLock() const;
        private:
            class Private;
            Private* d;
    };
}
#endif // SERVER_CACHE
