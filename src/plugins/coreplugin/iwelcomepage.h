
#ifndef IWELCOMEPAGE_H
#define IWELCOMEPAGE_H

#include "core_global.h"

#include "id.h"

#include <QObject>
#include <QUrl>

QT_FORWARD_DECLARE_CLASS(QQmlEngine)

namespace Core {

class CORE_EXPORT IWelcomePage : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(QUrl pageLocation READ pageLocation CONSTANT)
    Q_PROPERTY(int priority READ priority CONSTANT)
    Q_PROPERTY(bool hasSearchBar READ hasSearchBar CONSTANT)

public:
    IWelcomePage();
    virtual ~IWelcomePage();

    virtual QUrl pageLocation() const = 0;
    virtual QString title() const = 0;
    virtual int priority() const { return 0; }
    virtual void facilitateQml(QQmlEngine *) {}
    virtual bool hasSearchBar() const { return false; }
    virtual Core::Id id() const = 0;
};

} // Core

#endif // IWELCOMEPAGE_H
