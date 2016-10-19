#ifndef MIME_PART_IODEVICE_H
#define MIME_PART_IODEVICE_H

#include <QIODevice>

namespace Server
{
    class MimePartIODevice : public QIODevice
    {
        Q_OBJECT
        public:
            MimePartIODevice(QIODevice* source, const QByteArray& boundary, QObject* parent = 0);
            virtual ~MimePartIODevice();
            virtual bool isSequential() const;

            QByteArray boundary() const;
            QIODevice* source() const;
        protected:
            virtual qint64 readData(char* data, qint64 maxSize);
            virtual qint64 writeData(const char* data, qint64 maxSize);
        private:
            class Private;
            Private* d;
    };
};
#endif // MIME_PART_IODEVICE_H
