#ifndef VOLLEYBALL_SPORT_H
#define VOLLEYBALL_SPORT_H

#include <coreplugin/isport.h>

#include <QtCore/QObject>

namespace Volleyball {

namespace Internal {

class VolleyballSport : public Core::ISport
{
public:
    explicit VolleyballSport(QObject *parent = 0);
    ~VolleyballSport();

    QString title() const;
    int priority() const;
    Core::Id id() const;
    QIcon icon() const;
};

}
}
#endif // VOLLEYBALL_SPORT_H
