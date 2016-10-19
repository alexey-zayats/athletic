#ifndef CACHEENTRYPRIVATE_H
#define CACHEENTRYPRIVATE_H

#include "cacheentry.h"

namespace Server
{
    class CacheEntry::Private : public QSharedData
    {
        public:
            Private();
            Private(const QDateTime& timeStamp, const QByteArray& data);
            Private(const Private& other);
            ~Private();

            QDateTime timeStamp;
            QByteArray data;
    };
};
#endif // CACHEENTRYPRIVATE_H
