#include "clientiodevice.h"

namespace Server
{
    ClientIODevice::ClientIODevice(QObject* parent)
    : QIODevice(parent)
    {
    }

    ClientIODevice::~ClientIODevice()
    {
    }

    bool ClientIODevice::isSequential() const
    {
        return true;
    }
};
