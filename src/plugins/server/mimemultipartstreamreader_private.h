#ifndef MIMEMULTIPART_STREAM_READER_PRIVATE_H
#define MIMEMULTIPART_STREAM_READER_PRIVATE_H

#include "mimemultipartstreamreader.h"

#include <QIODevice>
#include <QPointer>

namespace Server
{
    class MimeMultipartStreamReader::Private
    {
        public:
            Private(QIODevice* device, const QByteArray& boundary);
            ~Private();

            QIODevice* m_device;
            QByteArray m_boundary;

            MimeMultipartStreamReader::TokenType m_tokenType;

            QString m_headerName;
            QString m_headerValue;

            QPointer<QIODevice> m_content;
    };
};
#endif // MIMEMULTIPART_STREAM_READER_PRIVATE_H
