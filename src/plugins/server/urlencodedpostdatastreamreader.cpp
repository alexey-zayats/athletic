#include "urlencodedpostdatastreamreader.h"

#include <QDebug>

namespace Server
{
    UrlEncodedPostDataStreamReader::UrlEncodedPostDataStreamReader(QIODevice* source)
    : PostDataStreamReaderBackend(source)
    , m_bytesRead(0)
    {
    }

    UrlEncodedPostDataStreamReader::~UrlEncodedPostDataStreamReader()
    {
        delete m_content;
    }

    int UrlEncodedPostDataStreamReader::readUntil(char character, char alternative)
    {
        const int initialIndex = m_buffer.indexOf(character);
        if(initialIndex != -1)
        {
            return initialIndex;
        }
        Q_ASSERT(source()->isOpen());
        Q_ASSERT(source()->isReadable());
        while(!source()->atEnd())
        {
            char next;
            if(!source()->getChar(&next))
            {
                break;
            }
            ++m_bytesRead;
            m_buffer.append(next);
            if(next == character || (alternative && (next == alternative)))
            {
                return m_buffer.length() - 1;
            }
        }
        return -1;
    }

    PostDataStreamReader::TokenType UrlEncodedPostDataStreamReader::readNext()
    {
        if(m_content)
        {
            Q_ASSERT(m_content->isOpen());
            m_content->readAll();
            delete m_content;
        }
        switch(tokenType())
        {
            case PostDataStreamReader::Invalid:
                if(m_lastValidTokenType != PostDataStreamReader::Invalid)
                {
                    m_tokenType = m_lastValidTokenType;
                    return readNext();
                }
                break;
            case PostDataStreamReader::NoToken:
                m_tokenType = PostDataStreamReader::StartData;
                break;
            case PostDataStreamReader::StartData:
            case PostDataStreamReader::VariableValue:
                {
                    // Expect: foo=bar[&...]
                    const int count = readUntil('=', '&');
                    if(count == -1 && !source()->atEnd())
                    {
                        // Syntax error, can't continue
                        m_lastValidTokenType = PostDataStreamReader::Invalid;
                        m_tokenType = PostDataStreamReader::Invalid;
                        break;
                    }
                    if(m_buffer.isEmpty())
                    {
                        Q_ASSERT(source()->atEnd());
                        if(m_bytesRead == source()->size())
                        {
                            m_tokenType = PostDataStreamReader::EndData;
                        }
                        else
                        {
                            m_lastValidTokenType = m_tokenType;
                            m_tokenType = PostDataStreamReader::Invalid;
                        }
                        break;
                    }
                    m_variableName = QUrl::fromPercentEncoding(m_buffer.left(count));
                    if(count == -1)
                    {
                        m_buffer.clear();
                    }
                    else
                    {
                        m_buffer = m_buffer.mid(count);
                        // Remaining: $, &foo=bar[&...], =bar[...]
                    }
                    m_tokenType = PostDataStreamReader::VariableName;
                }
                break;
            case PostDataStreamReader::VariableName:
                // Expected: $, &foo=bar[...], =bar[...]
                if(m_buffer.isEmpty()) // $
                {
                    m_variableValue.clear();
                    m_tokenType = PostDataStreamReader::EndData;
                    break;
                }

                Q_ASSERT(!m_buffer.isEmpty());
                if(m_buffer.at(0) == '&')
                {
                    m_variableValue.clear();
                    m_buffer = m_buffer.mid(1);
                    // Remaining: foo=bar[&...]
                }
                else
                {
                    Q_ASSERT(m_buffer.at(0) == '=');
                    const int end = readUntil('&');
                    if(end == -1)
                    {
                        m_variableValue = QUrl::fromPercentEncoding(m_buffer.mid(1));
                        m_buffer.clear();
                    }
                    else
                    {
                        const int length = end - 1;
                        m_variableValue = QUrl::fromPercentEncoding(m_buffer.mid(1, length));
                        m_buffer = m_buffer.mid(end + 1);
                        // Remaining: foo=bar[&...]
                    }
                }
                m_tokenType = PostDataStreamReader::VariableValue;
                break;
            default:
                // EndData: fine; FileHeader/FileValue: uh... what?
                m_lastValidTokenType = PostDataStreamReader::Invalid;
                m_tokenType = PostDataStreamReader::Invalid;
                break;

        }
        return tokenType();
    }
};
