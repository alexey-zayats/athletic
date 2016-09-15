#ifndef HANDBALL_SPORT_H
#define HANDBALL_SPORT_H

#include <coreplugin/isport.h>

#include <QtCore/QObject>

namespace Handball {

namespace Internal {

class HandballSport : public Core::ISport
{
public:
    explicit HandballSport(QObject *parent = 0);
    ~HandballSport();

    QString title() const;
    int priority() const;
    Core::Id id() const;
    QIcon icon() const;
};

}
}
#endif // HANDBALL_SPORT_H
