#ifndef PRESPAWNEDSPAWNER_H
#define PRESPAWNEDSPAWNER_H

#include "abstractresponder.h"
#include "server_global.h"

namespace Server
{
    class SERVER_EXPORT PrespawnedSpawner : public SpawnerBase
    {
        public:
            PrespawnedSpawner(QObject* object);
            QObject* spawn(QObject* parent) const;
            bool persist() const;
        private:
            QObject* m_object;
    };
};
#endif // PRESPAWNEDSPAWNER_H
