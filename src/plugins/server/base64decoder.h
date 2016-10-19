#ifndef BASE64DECODER_H
#define BASE64DECODER_H

#include <QByteArray>
#include <QIODevice>

namespace Server
{
    class Base64Decoder : public QIODevice
    {
        Q_OBJECT
        public:
            Base64Decoder(QIODevice* source, QObject* parent = 0);
            virtual ~Base64Decoder();
            virtual bool isSequential() const;
            virtual bool atEnd() const;

            QIODevice* source() const;
        protected:
            virtual qint64 readData(char* data, qint64 maxSize);
            virtual qint64 writeData(const char* data, qint64 maxSize);
        private:
            class Private;
            Private* d;
    };
};
#endif // BASE64DECODER_H
