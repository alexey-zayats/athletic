#ifndef URLENCODEDPOSTDATASTREAMREADER_H
#define URLENCODEDPOSTDATASTREAMREADER_H

#include "postdatastreamreaderbackend.h"

namespace Server
{
    class UrlEncodedPostDataStreamReader : public PostDataStreamReaderBackend
    {
        public:
            UrlEncodedPostDataStreamReader(QIODevice* source);
            virtual ~UrlEncodedPostDataStreamReader();
            virtual PostDataStreamReader::TokenType readNext();
        private:
            int readUntil(char character, char alternative = 0);
            QByteArray m_buffer;
            qint64 m_bytesRead;
    };
};
#endif // URLENCODEDPOSTDATASTREAMREADER_H
