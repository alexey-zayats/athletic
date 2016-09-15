#ifndef WEIGHTLIFTING_SPORT_H
#define WEIGHTLIFTING_SPORT_H

#include <coreplugin/isport.h>

#include <QtCore/QObject>

namespace WeightLifting {

namespace Internal {

class WeightLiftingSport : public Core::ISport
{
public:
    explicit WeightLiftingSport(QObject *parent = 0);
    ~WeightLiftingSport();

    QString title() const;
    int priority() const;
    Core::Id id() const;
    QIcon icon() const;
};

}
}
#endif // WEIGHTLIFTING_SPORT_H
