#ifndef JUDOSPORT_H
#define JUDOSPORT_H

#include <coreplugin/isport.h>

#include <QtCore/QObject>

namespace Judo {

namespace Internal {

class JudoSport : public Core::ISport
{
public:
    explicit JudoSport(QObject *parent = 0);
    ~JudoSport();

    QString title() const;
    int priority() const;
    Core::Id id() const;
    QIcon icon() const;
};

}
}
#endif // JUDOSPORT_H
