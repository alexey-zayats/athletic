#include "abstractresponder.h"

namespace Server
{
    SpawnerBase::SpawnerBase()
    {
    }

    SpawnerBase::~SpawnerBase()
    {
    }

    AbstractResponder::AbstractResponder(QObject* parent)
    : QObject(parent)
    {
    }

    AbstractResponder::~AbstractResponder()
    {
    }
};
