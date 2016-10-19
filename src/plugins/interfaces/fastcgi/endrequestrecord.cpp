#include "endrequestrecord.h"

#include "recordheader.h"

namespace FastCgi
{
    QByteArray EndRequestRecord::create(quint16 requestId)
    {
        FCGI_EndRequestBody body;
        ::memset(&body, 0, sizeof(body));
        body.protocolStatus = FCGI_REQUEST_COMPLETE;
        return RecordHeader::create(
            requestId,
            RecordHeader::EndRequestRecord,
            QByteArray::fromRawData(
                reinterpret_cast<const char*>(&body),
                sizeof(body)
            )
        );
    }
}
