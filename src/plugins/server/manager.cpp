#include "manager.h"
#include "manager_private.h"

#include <extensionsystem/pluginmanager.h>

#include <QSettings>

namespace Server
{
    Manager::Manager(QObject* parent)
        :
            QObject(parent),
            d(new Private(this))
    {
        connect(
            d,
            SIGNAL(newRequest(Server::Request*)),
            this,
            SIGNAL(newRequest(Server::Request*))
        );
    }

    Manager::Manager(const char* backend, const QMap<QString, QVariant>& configuration, QObject* parent)
        :
            QObject(parent),
            d(0)
    {
        // todo: some nicer way
        {
            QSettings *settings = ExtensionSystem::PluginManager::settings();

            settings->beginGroup( QLatin1String("Server") );
            settings->setValue( QLatin1String("socketType") , QString::fromLatin1(backend));
            for(
                QMap<QString, QVariant>::ConstIterator it = configuration.constBegin();
                it != configuration.constEnd();
                ++it
            )
            {
                settings->setValue(it.key(), it.value());
            }
            settings->endGroup();
            settings->sync();
        }

        d = new Private(this);
        connect(
            d,
            SIGNAL(newRequest(Server::Request*)),
            this,
            SIGNAL(newRequest(Server::Request*))
        );
    }

    Manager::~Manager()
    {
    }
}
