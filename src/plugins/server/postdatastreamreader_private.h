#ifndef POSTDATASTREAMREADER_PRIVATE_H
#define POSTDATASTREAMREADER_PRIVATE_H

#include "postdatastreamreader.h"
#include "postdatastreamreaderbackend.h"

namespace Server
{
    class PostDataStreamReader::Private
    {
        public:
            PostDataStreamReaderBackend* m_backend;
    };
};
#endif // POSTDATASTREAMREADER_PRIVATE_H
