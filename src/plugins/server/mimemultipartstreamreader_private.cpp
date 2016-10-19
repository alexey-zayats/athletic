#include "mimemultipartstreamreader_private.h"

#include <QDebug>
#include <QStringList>

namespace Server
{
    MimeMultipartStreamReader::Private::Private(QIODevice* device)
    : m_device(device)
    , m_tokenType(NoToken)
    , m_content(0)
    {
    }

    MimeMultipartStreamReader::Private::Private(QIODevice* device, const QByteArray& boundary)
    : m_device(device)
    , m_boundary(boundary)
    , m_tokenType(NoToken)
    , m_content(0)
    {
    }

    MimeMultipartStreamReader::Private::~Private()
    {
        delete m_content;
    }

    void MimeMultipartStreamReader::Private::parseHeader()
    {
        Q_ASSERT(m_tokenType == DocumentHeader);
        if(m_headerName.toUpper() == QLatin1String("CONTENT-TYPE") )
        {
            const QStringList parts = m_headerValue.split( QLatin1String("; ") );
            Q_FOREACH(const QString& part, parts)
            {
                if(part.startsWith( QLatin1String("boundary=") ))
                {
                    const int startPosition = part.indexOf( QLatin1Char('"') );
                    const int endPosition = part.indexOf( QLatin1Char('"') , startPosition + 1) - 1;
                    const int count = endPosition - startPosition;
                    Q_ASSERT(startPosition != -1);
                    Q_ASSERT(endPosition != -1);
                    Q_ASSERT(count > 0);
                    m_boundary = part.mid(startPosition + 1, count).toLatin1();
                    //qDebug() << "Parsed boundary as" << m_boundary;
                }
            }
        }
    }
};
