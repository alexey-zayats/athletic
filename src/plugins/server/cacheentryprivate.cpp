#include "cacheentryprivate.h"

namespace Server
{
    CacheEntry::Private::Private()
    : QSharedData()
    {
    }

    CacheEntry::Private::Private(const QDateTime& _timeStamp, const QByteArray& _data)
    {
        timeStamp = _timeStamp;
        data = _data;
    }

    CacheEntry::Private::Private(const Private& other)
    : QSharedData(other)
    , timeStamp(other.timeStamp)
    , data(other.data)
    {
    }

    CacheEntry::Private::~Private()
    {
    }
};
