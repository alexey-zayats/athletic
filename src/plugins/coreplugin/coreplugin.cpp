
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
    qCDebug(corepluginLog) << "CorePlugin";
    mainWindow = new QMainWindow();
}

CorePlugin::~CorePlugin()
{
    qCDebug(corepluginLog) << "~CorePlugin";
    delete mainWindow;
}

bool CorePlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    qCDebug(corepluginLog) << "initialize";

    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    return true;
}

void CorePlugin::extensionsInitialized()
{
    qCDebug(corepluginLog) << "extensionsInitialized";
    mainWindow->show();
    initStyle();
}

bool CorePlugin::delayedInitialize()
{
    qCDebug(corepluginLog) << "delayedInitialize";
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag CorePlugin::aboutToShutdown()
{
    qCDebug(corepluginLog) << "aboutToShutdownn";

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
