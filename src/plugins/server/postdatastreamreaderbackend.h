#ifndef POSTDATASTREAMREADERBACKEND_H
#define POSTDATASTREAMREADERBACKEND_H

#include "postdatastreamreader.h"

#include <QIODevice>
#include <QPointer>

namespace Server
{
    class PostDataStreamReaderBackend
    {
        public:
            PostDataStreamReaderBackend(QIODevice* source);
            virtual ~PostDataStreamReaderBackend();
            virtual bool atEnd() const;
            QIODevice* source() const;

            PostDataStreamReader::TokenType tokenType() const;
            QString variableName() const;
            QString variableValue() const;
            QIODevice* fileContents() const;
            QString fileName() const;
            QString mimeType() const;

            virtual PostDataStreamReader::TokenType readNext() = 0;
        protected:
            PostDataStreamReader::TokenType m_tokenType;
            PostDataStreamReader::TokenType m_lastValidTokenType;
            QString m_variableName;
            QString m_variableValue;
            QPointer<QIODevice> m_content;
            QString m_filename;
            QString m_mimeType;
        private:
            QIODevice* m_source;
    };
};
#endif // POSTDATASTREAMREADERBACKEND_H
