#ifndef TENNIS_SPORT_H
#define TENNIS_SPORT_H

#include <coreplugin/isport.h>

#include <QtCore/QObject>

namespace Tennis {

namespace Internal {

class TennisSport : public Core::ISport
{
public:
    explicit TennisSport(QObject *parent = 0);
    ~TennisSport();

    QString title() const;
    int priority() const;
    Core::Id id() const;
    QIcon icon() const;
};

}
}
#endif // TENNIS_SPORT_H
