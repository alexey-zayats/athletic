#ifndef BASE64DECODER_PRIVATE_H
#define BASE64DECODER_PRIVATE_H

#include "base64decoder.h"

namespace Server
{
    class Base64Decoder::Private
    {
        public:
            Private(QIODevice* source);
            ~Private();

            QIODevice* m_source;
            QByteArray m_encodedBuffer;
            QByteArray m_decodedBuffer;

            QByteArray readWithoutWhitespace(int count);
    };
};
#endif // BASE64DECODER_PRIVATE_H
