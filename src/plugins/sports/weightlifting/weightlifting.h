#ifndef WEIGHTLIFTING_PLUGIN_H
#define WEIGHTLIFTING_PLUGIN_H

#include <extensionsystem/iplugin.h>

#include "weightlifting_global.h"

namespace WeightLifting {

namespace Internal {

class WeightLiftingSport;

using namespace ExtensionSystem;

class WeightLiftingPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "weightlifting.json")

public:
    WeightLiftingPlugin();
    ~WeightLiftingPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    bool delayedInitialize();
    ShutdownFlag aboutToShutdown();

private slots:

private:
    WeightLiftingSport *m_weightLiftingSport;
};

} // namespace Internal
} // namespace WeightLifting

#endif // WEIGHTLIFTING_PLUGIN_H
