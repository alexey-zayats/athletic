#ifndef TAEKWONDOSPORT_H
#define TAEKWONDOSPORT_H

#include <coreplugin/isport.h>

#include <QtCore/QObject>

namespace Taekwondo {

namespace Internal {

class TaekwondoSport : public Core::ISport
{
public:
    explicit TaekwondoSport(QObject *parent = 0);
    ~TaekwondoSport();

    QString title() const;
    int priority() const;
    Core::Id id() const;
    QIcon icon() const;
};

}
}
#endif // TAEKWONDOSPORT_H
