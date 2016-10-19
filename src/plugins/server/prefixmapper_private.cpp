#include "prefixmapper_private.h"
#include "request.h"

#include <QVariant>

const char* PrefixTrackingProperty = "PREFIXMAPPER_PREFIX";
const char* SuffixTrackingProperty = "PREFIXMAPPER_SUFFIX";

namespace Server
{
    void PrefixMapper::Private::setPrefix(Request* request, const QByteArray& value)
    {
        request->setProperty(PrefixTrackingProperty, value);
    }

    void PrefixMapper::Private::setSuffix(Request* request, const QByteArray& value)
    {
        request->setProperty(SuffixTrackingProperty, value);
    }

    QByteArray PrefixMapper::Private::prefix(Request* request)
    {
        return request->property(PrefixTrackingProperty).toByteArray();
    }

    QByteArray PrefixMapper::Private::suffix(Request* request)
    {
        const QByteArray suffix = request->property(SuffixTrackingProperty).toByteArray();
        if(suffix.isNull())
        {
            return request->rawValue(ServerData, "PATH_INFO");
        }
        return suffix;
    }
};
