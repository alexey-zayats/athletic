#ifndef ROWINGSPORT_H
#define ROWINGSPORT_H

#include <coreplugin/isport.h>

#include <QtCore/QObject>

namespace Rowing {

namespace Internal {

class RowingSport : public Core::ISport
{
public:
    explicit RowingSport(QObject *parent = 0);
    ~RowingSport();

    QString title() const;
    int priority() const;
    Core::Id id() const;
    QIcon icon() const;
};

}
}
#endif // ROWINGSPORT_H
