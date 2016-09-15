#ifndef TABLETENNIS_PLUGIN_H
#define TABLETENNIS_PLUGIN_H

#include <extensionsystem/iplugin.h>

#include "tabletennis_global.h"

namespace TableTennis {

namespace Internal {

class TableTennisSport;

using namespace ExtensionSystem;

class TableTennisPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "tabletennis.json")

public:
    TableTennisPlugin();
    ~TableTennisPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    TableTennisSport *m_tableTennisSport;
};

} // namespace Internal
} // namespace TableTennis

#endif // TABLETENNIS_PLUGIN_H
