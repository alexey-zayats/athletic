#include "mimemultipartstreamreader_private.h"

#include <QDebug>
#include <QStringList>

namespace Server
{
    MimeMultipartStreamReader::Private::Private(QIODevice* device, const QByteArray& boundary)
    : m_device(device)
    , m_boundary(boundary)
    , m_tokenType(StartDocument)
    , m_content(0)
    {
    }

    MimeMultipartStreamReader::Private::~Private()
    {
        delete m_content;
    }

};
