#include "uploadedfile.h"

namespace Server {

UploadedFile::UploadedFile() :
    m_file(0)
{
    m_file = new QTemporaryFile();
    if ( m_file->open() )
        open(QIODevice::ReadWrite);
}

UploadedFile::~UploadedFile()
{
    m_file->close();
    delete m_file;
}

void UploadedFile::setName(const QByteArray &name)
{
    m_name = name;
}

QByteArray UploadedFile::name()
{
    return m_name;
}

void UploadedFile::setInfo(QHash<QByteArray,QByteArray> info)
{
    m_info = info;
}

qint64 UploadedFile::size() const
{
    Q_ASSERT(m_file);
    return m_file->size();
}

void UploadedFile::setFilename(const QByteArray &filename)
{
    m_filename = filename;
}

QByteArray UploadedFile::filename()
{
    return m_filename;
}

qint64 UploadedFile::bytesAvailable() const
{
    Q_ASSERT(m_file);
    return m_file->bytesAvailable();
}

qint64 UploadedFile::pos() const
{
    Q_ASSERT(m_file);
    return m_file->pos();
}

bool UploadedFile::seek(qint64 pos)
{
    Q_ASSERT(m_file);
    QIODevice::seek(pos);
    return m_file->seek(pos);
}

bool UploadedFile::isSequential() const
{
    Q_ASSERT(m_file);
    return m_file->isSequential();
}

qint64 UploadedFile::readData(char* data, qint64 maxSize)
{
    Q_ASSERT(m_file);
    return m_file->read(data, maxSize);
}

qint64 UploadedFile::writeData(const char* data, qint64 maxSize)
{
    Q_ASSERT(m_file);
    return m_file->write(data, maxSize);
}

QString UploadedFile::tmpName() const
{
    Q_ASSERT(m_file);
    return m_file->fileName();
}

}
