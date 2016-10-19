#ifndef MIMEMULTIPART_STREAM_READER_H
#define MIMEMULTIPART_STREAM_READER_H

class QByteArray;
class QIODevice;

#include <QString>

namespace Server
{
    class MimeMultipartStreamReader
    {
        public:
            enum TokenType
            {
                Invalid        = 0,
                NoToken        = 1,
                StartDocument  = 2,
                DocumentHeader = 3,
                IgnoredContent = 4,
                EndPart        = 5,
                StartPart      = 6,
                PartHeader     = 7,
                PartContent    = 8,
                EndDocument    = 9
            };
            /// Create a new MimeMultipartStreamReader, expecting document headers.
            MimeMultipartStreamReader(QIODevice* device);
            /// Create a new MimeMultipartStreamReader, expecting the first (ignored) content blob
            MimeMultipartStreamReader(QIODevice* device, const QByteArray& boundary);
            ~MimeMultipartStreamReader();
            bool atEnd() const;
            QIODevice* device() const;
            TokenType tokenType() const;
            TokenType readNext();

            /** If tokenType() is DocumentHeader or PartHeader, returns the header name.
             *
             * Otherwise, an empty string is returned.
             */
            QString headerName() const;
            /** If tokenType() is DocumentHeader or PartHeader, returns the header value.
             *
             * Otherwise, an empty string is returned.
             */
            QString headerValue() const;

            /** If tokenType() is IgnoredContent or PartContent, returns a QIODevice for reading the part.
             *
             * Otherwise, a null pointer is returned.
             *
             * The QIODevice remains owned by this object, and must not be deleted by the caller.
             */
            QIODevice* content() const;
        private:
            class Private;
            Private* d;
    };
};
#endif // MIMEMULTIPART_STREAM_READER_H
