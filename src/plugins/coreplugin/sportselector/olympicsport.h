#ifndef OLYMPICSPORT_H
#define OLYMPICSPORT_H

#include <QtCore/QObject>

#include "../isport.h"

namespace Core {

class OlympicSport : public Core::ISport
{
    Q_OBJECT

public:
    OlympicSport(QObject *parent = 0);
    ~OlympicSport();

    QString title() const;
    int priority() const;
    Core::Id id() const;
    QIcon icon() const;
};

}

#endif // OLYMPICSPORT_H
