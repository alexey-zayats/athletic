#ifndef PREFIXMAPPER_PRIVATE_H
#define PREFIXMAPPER_PRIVATE_H

#include "prefixmapper.h"

#include <QByteArray>
#include <QHash>

namespace Server
{
    class PrefixMapper::Private
    {
        public:
            struct Receiver
            {
                Receiver(SpawnerBase* _spawner, const char* _slot)
                : spawner(_spawner)
                , slot(_slot)
                {
                }

                Receiver()
                : spawner(0)
                , slot(0)
                {
                }

                SpawnerBase* spawner;
                const char* slot;

                operator bool() const { return slot && spawner; }
            };
            typedef QHash<QByteArray, Receiver> ServiceMap;
            ServiceMap services;
            AbstractResponder* responder;

            static void setPrefix(Request*, const QByteArray&);
            static void setSuffix(Request*, const QByteArray&);
            static QByteArray prefix(Request*);
            static QByteArray suffix(Request*);
    };
};
#endif // PREFIXMAPPER_PRIVATE_H
