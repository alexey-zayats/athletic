#ifndef UPLOADEDFILE_H
#define UPLOADEDFILE_H

#include <QTemporaryFile>
#include <QFile>
#include <QHash>
#include <QByteArray>

#include "server_global.h"

namespace Server
{

class SERVER_EXPORT UploadedFile
{
public:
    UploadedFile();
    ~UploadedFile();

    void setName(const QString&);
    QString name();

    QList<QByteArray> headers() { return m_info.keys(); }
    QByteArray header(QByteArray key) { return m_info.value(key); }

    void setInfo(QHash<QByteArray,QByteArray>);

    void setSize(int);
    int size();

    void setFilename(const QString&);
    QString filename();

    QFile *fp() { return m_file; }
    QString tmpFilename() { return m_file->fileName(); }

private:
    QFile *m_file;
    QString m_name;
    int m_size;
    QString m_filename;
    QHash<QByteArray,QByteArray> m_info;
};

}

#endif // UPLOADEDFILE_H
