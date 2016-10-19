#include "postdatastreamreader.h"
#include "postdatastreamreader_private.h"
#include "urlencodedpostdatastreamreader.h"

namespace Server
{
    PostDataStreamReader::PostDataStreamReader(Server::Request* request)
    : d(new Private())
    {
        d->m_backend = new UrlEncodedPostDataStreamReader(request);
    }

    PostDataStreamReader::~PostDataStreamReader()
    {
        delete d->m_backend;
        delete d;
    }

    bool PostDataStreamReader::atEnd() const
    {
        return d->m_backend->atEnd();
    }

    PostDataStreamReader::TokenType PostDataStreamReader::tokenType() const
    {
        return d->m_backend->tokenType();
    }

    PostDataStreamReader::TokenType PostDataStreamReader::readNext()
    {
        return d->m_backend->readNext();
    }

    QString PostDataStreamReader::variableName() const
    {
        return d->m_backend->variableName();
    }

    QString PostDataStreamReader::variableValue() const
    {
        return d->m_backend->variableValue();
    }

    QIODevice* PostDataStreamReader::fileContents() const
    {
        return d->m_backend->fileContents();
    }

    QString PostDataStreamReader::fileName() const
    {
        return d->m_backend->fileName();
    }

    QString PostDataStreamReader::mimeType() const
    {
        return d->m_backend->mimeType();
    }
};
