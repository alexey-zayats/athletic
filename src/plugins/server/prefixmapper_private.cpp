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
        qDebug() << value.isNull() << value.isEmpty();
    }

    QByteArray PrefixMapper::Private::prefix(Request* request)
    {
        return request->property(PrefixTrackingProperty).toByteArray();
    }

    QByteArray PrefixMapper::Private::suffix(Request* request)
    {
        QByteArray suffix;
        QVariant a = request->property(SuffixTrackingProperty);
        if ( a.isNull() ) {
            qDebug() << "suffix is null, set it to PATH_INFO";
            suffix = request->rawValue(ServerData, "PATH_INFO");
        } else {
            suffix = a.toByteArray();
        }
        qDebug() << suffix;
        return suffix;
    }
};
