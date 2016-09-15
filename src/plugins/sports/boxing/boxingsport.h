#ifndef BOXINGSPORT_H
#define BOXINGSPORT_H

#include <coreplugin/isport.h>

#include <QtCore/QObject>

namespace Boxing {

namespace Internal {

class BoxingSport : public Core::ISport
{
public:
    explicit BoxingSport(QObject *parent = 0);
    ~BoxingSport();

    QString title() const;
    int priority() const;
    Core::Id id() const;
    QIcon icon() const;
};

}
}
#endif // BOXINGSPORT_H
