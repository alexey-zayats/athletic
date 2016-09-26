#ifndef IMATCHCONTROL_H
#define IMATCHCONTROL_H

#include "core_global.h"

#include "id.h"

#include <QObject>
#include <QUrl>

namespace Core {

class CORE_EXPORT IMatchControl : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title CONSTANT)
    Q_PROPERTY(int priority READ priority CONSTANT)
    Q_PROPERTY(Core::Id id READ id CONSTANT)

public:
    IMatchControl();
    virtual ~IMatchControl();

    virtual QString title() const = 0;
    virtual int priority() const { return 0; }
    virtual Core::Id id() const = 0;
};

} // Core

#endif // IMATCHCONTROL_H
