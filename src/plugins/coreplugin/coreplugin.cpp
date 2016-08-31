
#include "coreplugin.h"

#include <QMainWindow>
#include <QFile>
#include <QApplication>

using namespace Core;
using namespace Core::Internal;
using namespace Utils;

Q_LOGGING_CATEGORY(corepluginLog, "athletic.plugins.coreplugin")

CorePlugin::CorePlugin()
{
    qCDebug(corepluginLog) << Q_FUNC_INFO;
    mainWindow = new QMainWindow();
}

CorePlugin::~CorePlugin()
{
    qCDebug(corepluginLog) << "destory coreplugin";
    delete mainWindow;
}

bool CorePlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    qCDebug(corepluginLog) << "init coreplugin";

    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    return true;
}

void CorePlugin::extensionsInitialized()
{
    qCDebug(corepluginLog) << "coreplugin initialized";
    mainWindow->show();
    initStyle();
}

bool CorePlugin::delayedInitialize()
{
    qCDebug(corepluginLog) << "coreplugin delaed initialize";
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag CorePlugin::aboutToShutdown()
{
    qCDebug(corepluginLog) << "try to shutdown";

    mainWindow->close();
    return SynchronousShutdown;
}

void CorePlugin::initStyle()
{
    QFile file( QLatin1String(":/css/core.css") );
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    mainWindow->setStyleSheet(styleSheet);
}
