#ifndef CURLINGSPORT_H
#define CURLINGSPORT_H

#include <coreplugin/isport.h>

#include <QtCore/QObject>

namespace Curling {

namespace Internal {

class CurlingSport : public Core::ISport
{
public:
    explicit CurlingSport(QObject *parent = 0);
    ~CurlingSport();

    QString title() const;
    int priority() const;
    Core::Id id() const;
    QIcon icon() const;
};

}
}
#endif // CURLINGSPORT_H
