#include "base64decoder.h"
#include "base64decoder_private.h"

#include "memcpy_safe.h"

#include <QDebug>

namespace Server
{
    Base64Decoder::Base64Decoder(QIODevice* source, QObject* parent)
    : QIODevice(parent)
    , d(new Private(source))
    {
    }

    Base64Decoder::~Base64Decoder()
    {
        delete d;
    }

    bool Base64Decoder::isSequential() const
    {
        return true;
    }

    QIODevice* Base64Decoder::source() const
    {
        return d->m_source;
    }

    bool Base64Decoder::atEnd() const
    {
        return QIODevice::atEnd() && source()->atEnd() && d->m_decodedBuffer.isEmpty();
    }

    qint64 Base64Decoder::readData(char* data, qint64 maxSize)
    {
        if(source()->atEnd())
        {
            if(!d->m_decodedBuffer.isEmpty())
            {
                const qint64 toCopy = qMin(maxSize, static_cast<qint64>(d->m_decodedBuffer.length()));
                ::memcpy_safe(data, maxSize, d->m_decodedBuffer.constData(), toCopy);
                if(toCopy == d->m_decodedBuffer.length())
                {
                    d->m_decodedBuffer.clear();
                }
                else
                {
                    d->m_decodedBuffer = d->m_decodedBuffer.mid(toCopy);
                }
                return toCopy;
            }
            return -1;
        }

        qint64 bytesRead = 0;
        qint64 toRead = maxSize - bytesRead;
        if(!d->m_decodedBuffer.isEmpty())
        {
            const int count = qMin(toRead, static_cast<qint64>(d->m_decodedBuffer.length()));
            ::memcpy_safe(data, maxSize, d->m_decodedBuffer.constData(), count);
            bytesRead += count;
            d->m_decodedBuffer = d->m_decodedBuffer.right(3 - count);
        }
        while(bytesRead < maxSize && !source()->atEnd())
        {
            // grab four non-whitespace bytes
            d->m_encodedBuffer.append(d->readWithoutWhitespace(4 - d->m_encodedBuffer.length()));
            if(d->m_encodedBuffer.length() == 4)
            {
                d->m_decodedBuffer.append(QByteArray::fromBase64(d->m_encodedBuffer));
                d->m_encodedBuffer.clear();
                const int count = qMin(toRead, static_cast<qint64>(d->m_decodedBuffer.length()));
                ::memcpy_safe(&data[bytesRead], maxSize - bytesRead, d->m_decodedBuffer.constData(), count);
                bytesRead += count;
                d->m_decodedBuffer = d->m_decodedBuffer.right(3 - count);
            }
            else
            {
                break;
            };
        }
        return bytesRead;
    }

    qint64 Base64Decoder::writeData(const char* data, qint64 maxSize)
    {
        Q_UNUSED(data);
        Q_UNUSED(maxSize);
        return -1;
    }
};
