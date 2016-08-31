#ifndef SYSTEMID_H
#define SYSTEMID_H

#include <QObject>

#include "utils_global.h"

namespace Utils {

class ATHLETIC_UTILS_EXPORT SystemID : public QObject
{
    Q_OBJECT
public:
    explicit SystemID(QObject *parent = 0);

    const QString getMachineName();
    unsigned short getCpuHash();
    unsigned short getVolumeHash();
    unsigned short getMacHash();
signals:

public slots:
private:
    unsigned short hashMacAddress( unsigned char* mac );
#ifndef Q_OS_MACX
    void getCpuid( unsigned int* p, unsigned int ax );
#endif
};

}

#endif // SYSTEMID_H
