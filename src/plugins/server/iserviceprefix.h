#ifndef ISERVICEPREFIX_H
#define ISERVICEPREFIX_H

#include <QtCore/QObject>

#include "server_global.h"
#include "abstractresponder.h"

#include <QObject>

namespace Server
{

class SERVER_EXPORT IServicePrefix : public QObject
{
    Q_OBJECT
public:
    explicit IServicePrefix(QObject *parent = 0);
    virtual ~IServicePrefix();

    virtual QString prefix() const = 0;
    virtual SpawnerBase *service() { return 0; }

signals:

public slots:
};

}

#endif // ISERVICEPREFIX_H
