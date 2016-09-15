#ifndef CANOEINGSPORT_H
#define CANOEINGSPORT_H

#include <coreplugin/isport.h>

#include <QtCore/QObject>

namespace Canoeing {

namespace Internal {

class CanoeingSport : public Core::ISport
{
public:
    explicit CanoeingSport(QObject *parent = 0);
    ~CanoeingSport();

    QString title() const;
    int priority() const;
    Core::Id id() const;
    QIcon icon() const;
};

}
}
#endif // CANOEINGSPORT_H
