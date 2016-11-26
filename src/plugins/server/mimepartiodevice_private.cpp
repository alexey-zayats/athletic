#include "mimepartiodevice_private.h"

namespace Server
{
    MimePartIODevice::Private::Private(QIODevice* source, const QByteArray& boundary)
    : m_atEnd(false)
    , m_boundary(boundary)
    , m_matcher("\r\n--" + boundary)
    , m_source(source)
    {
    }

    MimePartIODevice::Private::~Private()
    {
    }
};
