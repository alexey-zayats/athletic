#include "uploadedfile.h"

namespace Server {

UploadedFile::UploadedFile() :
    m_file(0)
{
//    m_file = new QTemporaryFile();
    m_file = new QFile(QLatin1String("/Users/alexis/tmp"));
    m_file->open(QFile::ReadWrite);
}

UploadedFile::~UploadedFile()
{
    m_file->close();
    delete m_file;
}

void UploadedFile::setName(const QString &name)
{
    m_name = name;
}

QString UploadedFile::name()
{
    return m_name;
}

void UploadedFile::setInfo(QHash<QByteArray,QByteArray> info)
{
    m_info = info;
}

void UploadedFile::setSize(int size)
{
    m_size = size;
}

int UploadedFile::size()
{
    return m_size;
}

void UploadedFile::setFilename(const QString &filename)
{
    m_filename = filename;
}

QString UploadedFile::filename()
{
    return m_filename;
}

}
