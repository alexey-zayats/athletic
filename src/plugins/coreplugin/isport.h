#ifndef ISPORT_H
#define ISPORT_H

#include "core_global.h"

#include "id.h"

#include <QObject>
#include <QUrl>
#include <QIcon>

namespace Core
{

class CORE_EXPORT ISport : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(int priority READ priority CONSTANT)
    Q_PROPERTY(Core::Id id READ id CONSTANT)
    Q_PROPERTY(QIcon icon READ icon CONSTANT)

public:
    explicit ISport(QObject *parent = 0);
    virtual ~ISport();

    virtual QString title() const = 0;
    virtual int priority() const { return 0; }
    virtual Core::Id id() const = 0;
    virtual QIcon icon() const = 0;

signals:

public slots:
};

}

#endif // ISPORT_H
