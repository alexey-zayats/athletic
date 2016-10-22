#include "parametersrecord.h"

#include "recordheader.h"
#include "unsignedbytearray.h"

#include <QDebug>

namespace FastCgi
{
    ParametersRecord::ParametersRecord(const RecordHeader& header, const QByteArray& _data)
    {
        const UnsignedByteArray data(_data);
        Q_ASSERT(header.type() == RecordHeader::ParametersRecord);
        Q_ASSERT(data.length() >= header.contentLength());

        quint16 i = 0;
        quint16 bytesToRead = header.contentLength();

        const quint8 highBitMask = 1 << 7;

        QByteArray name, value;

        while(i < bytesToRead)
        {
            quint32 nameLength;
            quint32 valueLength;

            // See "Name-Value pairs" in the spec

            // work out name length
            if(data[i] & highBitMask)
            {
                // Four bytes of name length
                nameLength =
                    ((data[i] & ~highBitMask) << 24)
                    + (data[i+1] << 16)
                    + (data[i+2] << 8)
                    + data[i+3]
                ;
                i+= 4;
            }
            else
            {
                // 1 byte of name length
                nameLength = data[i++];
            }

            // ditto for value
            if(data[i] & highBitMask)
            {
                // Four bytes of value length
                valueLength =
                    ((data[i] & ~highBitMask) << 24)
                    + (data[i+1] << 16)
                    + (data[i+2] << 8)
                    + data[i+3]
                ;
                i+= 4;
            }
            else
            {
                // 1 byte of name length
                valueLength = data[i++];
            }

            name = QByteArray(&data.constData()[i], nameLength);
            i += nameLength;
            value = QByteArray(&data.constData()[i], valueLength);
            i += valueLength;
            m_parameters.insert(name, value);
            name.clear();
            value.clear();
        }
    }

    bool ParametersRecord::isEmpty() const
    {
        return m_parameters.isEmpty();
    }

    Server::ClientIODevice::HeaderMap ParametersRecord::parameters() const
    {
        return m_parameters;
    }
}
