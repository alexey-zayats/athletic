#ifndef TABLETENNIS_SPORT_H
#define TABLETENNIS_SPORT_H

#include <coreplugin/isport.h>

#include <QtCore/QObject>

namespace TableTennis {

namespace Internal {

class TableTennisSport : public Core::ISport
{
public:
    explicit TableTennisSport(QObject *parent = 0);
    ~TableTennisSport();

    QString title() const;
    int priority() const;
    Core::Id id() const;
    QIcon icon() const;
};

}
}
#endif // TABLETENNIS_SPORT_H
