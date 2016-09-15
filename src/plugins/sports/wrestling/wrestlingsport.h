#ifndef WRESTLINGSPORT_H
#define WRESTLINGSPORT_H

#include <coreplugin/isport.h>

#include <QtCore/QObject>

namespace Wrestling {

namespace Internal {

class WrestlingSport : public Core::ISport
{
public:
    explicit WrestlingSport(QObject *parent = 0);
    ~WrestlingSport();

    QString title() const;
    int priority() const;
    Core::Id id() const;
    QIcon icon() const;
};

}
}
#endif // WRESTLINGSPORT_H
