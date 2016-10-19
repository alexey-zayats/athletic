#ifndef MIMEPARTIODEVICE_PRIVATE_H
#define MIMEPARTIODEVICE_PRIVATE_H

#include "mimepartiodevice.h"

#include <QByteArrayMatcher>

namespace Server
{
    class MimePartIODevice::Private
    {
        public:
            Private(QIODevice* source, const QByteArray& boundary);
            ~Private();
            bool m_atEnd;
            QByteArray m_boundary;
            QByteArrayMatcher m_matcher;
            QIODevice* m_source;
    };
};
#endif // MIMEPARTIODEVICE_PRIVATE_H
