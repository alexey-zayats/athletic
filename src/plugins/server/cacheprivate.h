#ifndef CACHEPRIVATE_H
#define CACHEPRIVATE_H

#include "cache.h"
#include "cachebackend.h"

namespace Server
{
    class Cache::Private
    {
        public:
            Private(const QString& cacheName);
            ~Private();

            CacheBackend* backend;
        private:
            void loadBackendFactory();

            static CacheBackend::Factory* m_backendFactory;
    };
};
#endif // CACHEPRIVATE_H
