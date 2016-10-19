#include "standardoutputrecord.h"

#include "recordheader.h"

namespace FastCgi
{
    QByteArray StandardOutputRecord::create(quint16 requestId, QByteArray data)
    {
        return RecordHeader::create(requestId, RecordHeader::StandardOutputRecord, data);
    };
}
