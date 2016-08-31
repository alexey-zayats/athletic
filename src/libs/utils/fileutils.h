#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QCoreApplication>
#include <QXmlStreamWriter> // Mac.
#include <QMetaType>
#include <QStringList>

#include <functional>

#include "utils_global.h"

namespace Utils {class FileName; }

QT_BEGIN_NAMESPACE
class QDataStream;
class QDateTime;
class QDir;
class QDropEvent;
class QFile;
class QFileInfo;
class QTemporaryFile;
class QTextStream;
class QWidget;

ATHLETIC_UTILS_EXPORT QDebug operator<<(QDebug dbg, const Utils::FileName &c);

QT_END_NAMESPACE

namespace Utils {

class ATHLETIC_UTILS_EXPORT FileName : private QString
{
public:
    FileName();
    explicit FileName(const QFileInfo &info);
    QFileInfo toFileInfo() const;
    static FileName fromString(const QString &filename);
    static FileName fromString(const QString &filename, const QString &defaultExtension);
    static FileName fromLatin1(const QByteArray &filename);
    static FileName fromUserInput(const QString &filename);
    static FileName fromUtf8(const char *filename, int filenameSize = -1);
    const QString &toString() const;
    QString toUserOutput() const;
    QString fileName(int pathComponents = 0) const;
    bool exists() const;

    FileName parentDir() const;

    bool operator==(const FileName &other) const;
    bool operator!=(const FileName &other) const;
    bool operator<(const FileName &other) const;
    bool operator<=(const FileName &other) const;
    bool operator>(const FileName &other) const;
    bool operator>=(const FileName &other) const;

    bool isChildOf(const FileName &s) const;
    bool isChildOf(const QDir &dir) const;
    bool endsWith(const QString &s) const;

    FileName relativeChildPath(const FileName &parent) const;
    FileName &appendPath(const QString &s);
    FileName &appendString(const QString &str);
    FileName &appendString(QChar str);

    using QString::size;
    using QString::count;
    using QString::length;
    using QString::isEmpty;
    using QString::isNull;
    using QString::clear;
private:
    FileName(const QString &string);
};

ATHLETIC_UTILS_EXPORT QTextStream &operator<<(QTextStream &s, const FileName &fn);

using FileNameList = QList<FileName>;

class ATHLETIC_UTILS_EXPORT FileUtils {
public:
    static bool removeRecursively(const FileName &filePath, QString *error = 0);
    static bool copyRecursively(const FileName &srcFilePath, const FileName &tgtFilePath,
                                QString *error = 0, const std::function<bool (QFileInfo, QFileInfo, QString *)> &copyHelper = std::function<bool (QFileInfo, QFileInfo, QString *)>());
    static bool isFileNewerThan(const FileName &filePath, const QDateTime &timeStamp);
    static FileName resolveSymlinks(const FileName &path);
    static FileName canonicalPath(const FileName &path);
    static QString shortNativePath(const FileName &path);
    static QString fileSystemFriendlyName(const QString &name);
    static int indexOfQmakeUnfriendly(const QString &name, int startpos = 0);
    static QString qmakeFriendlyName(const QString &name);
    static bool makeWritable(const FileName &path);
    static QString normalizePathName(const QString &name);

    static bool isRelativePath(const QString &fileName);
    static bool isAbsolutePath(const QString &fileName) { return !isRelativePath(fileName); }
    static QString resolvePath(const QString &baseDir, const QString &fileName);
};

class ATHLETIC_UTILS_EXPORT FileReader
{
    Q_DECLARE_TR_FUNCTIONS(Utils::FileUtils) // sic!
public:
    static QByteArray fetchQrc(const QString &fileName); // Only for internal resources
    bool fetch(const QString &fileName, QIODevice::OpenMode mode = QIODevice::NotOpen); // QIODevice::ReadOnly is implicit
    bool fetch(const QString &fileName, QIODevice::OpenMode mode, QString *errorString);
    bool fetch(const QString &fileName, QString *errorString)
        { return fetch(fileName, QIODevice::NotOpen, errorString); }
    bool fetch(const QString &fileName, QIODevice::OpenMode mode, QWidget *parent);
    bool fetch(const QString &fileName, QWidget *parent)
        { return fetch(fileName, QIODevice::NotOpen, parent); }
    const QByteArray &data() const { return m_data; }
    const QString &errorString() const { return m_errorString; }
private:
    QByteArray m_data;
    QString m_errorString;
};

class ATHLETIC_UTILS_EXPORT FileSaverBase
{
    Q_DECLARE_TR_FUNCTIONS(Utils::FileUtils) // sic!
public:
    FileSaverBase();
    virtual ~FileSaverBase();

    QString fileName() const { return m_fileName; }
    bool hasError() const { return m_hasError; }
    QString errorString() const { return m_errorString; }
    virtual bool finalize();
    bool finalize(QString *errStr);
    bool finalize(QWidget *parent);

    bool write(const char *data, int len);
    bool write(const QByteArray &bytes);
    bool setResult(QTextStream *stream);
    bool setResult(QDataStream *stream);
    bool setResult(QXmlStreamWriter *stream);
    bool setResult(bool ok);

protected:
    QFile *m_file;
    QString m_fileName;
    QString m_errorString;
    bool m_hasError;

private:
    Q_DISABLE_COPY(FileSaverBase)
};

class ATHLETIC_UTILS_EXPORT FileSaver : public FileSaverBase
{
    Q_DECLARE_TR_FUNCTIONS(Utils::FileUtils) // sic!
public:
    explicit FileSaver(const QString &filename, QIODevice::OpenMode mode = QIODevice::NotOpen); // QIODevice::WriteOnly is implicit

    virtual bool finalize();
    using FileSaverBase::finalize;
    QFile *file() { return m_file; }

private:
    bool m_isSafe;
};

class ATHLETIC_UTILS_EXPORT TempFileSaver : public FileSaverBase
{
    Q_DECLARE_TR_FUNCTIONS(Utils::FileUtils) // sic!
public:
    explicit TempFileSaver(const QString &templ = QString());
    ~TempFileSaver();

    QTemporaryFile *file() { return reinterpret_cast<QTemporaryFile *>(m_file); }

    void setAutoRemove(bool on) { m_autoRemove = on; }

private:
    bool m_autoRemove;
};

} // namespace Utils

QT_BEGIN_NAMESPACE
ATHLETIC_UTILS_EXPORT uint qHash(const Utils::FileName &a);
QT_END_NAMESPACE

Q_DECLARE_METATYPE(Utils::FileName)

#endif // FILEUTILS_H