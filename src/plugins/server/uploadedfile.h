#ifndef UPLOADEDFILE_H
#define UPLOADEDFILE_H

#include <QTemporaryFile>
#include <QFile>
#include <QHash>
#include <QByteArray>
#include <QIODevice>

#include "server_global.h"

namespace Server
{

class SERVER_EXPORT UploadedFile : public QIODevice
{
public:
    UploadedFile();
    ~UploadedFile();

    qint64 bytesAvailable() const;
    qint64 pos() const;
    bool seek(qint64 pos);

    bool isSequential() const;

    void setName(const QByteArray&);
    QByteArray name();

    QList<QByteArray> headers() { return m_info.keys(); }
    QByteArray header(QByteArray key) { return m_info.value(key); }

    void setInfo(QHash<QByteArray,QByteArray>);

    qint64 size() const;

    void setFilename(const QByteArray&);
    QByteArray filename();

    QString tmpName() const;

protected:
    /// Read data from buffer
    qint64 readData(char* data, qint64 maxSize);
    /// Write a FastCGI STDOUT record
    qint64 writeData(const char* data, qint64 maxSize);
    QTemporaryFile *m_file;

private:

    QByteArray m_name;
    QByteArray m_filename;
    QHash<QByteArray,QByteArray> m_info;
};

}

#endif // UPLOADEDFILE_H
