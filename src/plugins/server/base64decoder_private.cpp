#include "base64decoder_private.h"

#include <QDebug>

namespace Server
{
    Base64Decoder::Private::Private(QIODevice* source)
    : m_source(source)
    {
    }

    Base64Decoder::Private::~Private()
    {
    }

    QByteArray Base64Decoder::Private::readWithoutWhitespace(int count)
    {
        QByteArray out;
        while(out.length() < count && !m_source->atEnd())
        {
            char foo;
            if(!m_source->getChar(&foo))
            {
                break;
            }
            if(!QChar( QLatin1Char(foo) ).isSpace())
            {
                out.append(foo);
            }
        }
        return out;
    }
};
