
#include "coreplugin.h"
#include "mainwindow.h"
#include "id.h"
#include "themechooser.h"
#include "icore.h"
#include "coreconstants.h"
#include "actionmanager/actionmanager.h"
#include "find/findplugin.h"
#include "editmode.h"
#include "modemanager.h"

#include <utils/algorithm.h>
#include <utils/stringutils.h>
#include <utils/theme/theme.h>
#include <utils/theme/theme_p.h>

#include <extensionsystem/pluginmanager.h>
#include <extensionsystem/pluginerroroverview.h>

#include <QMainWindow>
#include <QFile>
#include <QApplication>

using namespace Core;
using namespace Core::Internal;
using namespace Utils;

Q_LOGGING_CATEGORY(corepluginLog, "athletic.plugins.coreplugin")

CorePlugin::CorePlugin()
{
    qRegisterMetaType<Id>();
}

CorePlugin::~CorePlugin()
{
    delete m_mainWindow;
    setCreatorTheme(0);
}

bool CorePlugin::initialize(const QStringList &arguments, QString *errorMessage)
{
    Q_UNUSED(arguments);
    Q_UNUSED(errorMessage);

    if (ThemeEntry::availableThemes().isEmpty()) {
        *errorMessage = tr("No themes found in installation.");
        return false;
    }

    new ActionManager(this);
    Theme::initialPalette(); // Initialize palette before setting it



    const Id settingsThemeId = Id::fromSetting(
                ICore::settings()->value(QLatin1String(Constants::SETTINGS_THEME),
                                         QLatin1String(Constants::DEFAULT_THEME)));
     Id themeId = settingsThemeId;
     QColor overrideColor;
     bool presentationMode = false;

     for (int i = 0; i < arguments.size(); ++i) {
         if (arguments.at(i) == QLatin1String("-color")) {
             const QString colorcode(arguments.at(i + 1));
             overrideColor = QColor(colorcode);
             i++; // skip the argument
         }
         if (arguments.at(i) == QLatin1String("-presentationMode"))
             presentationMode = true;
         if (arguments.at(i) == QLatin1String("-theme")) {
             themeId = Id::fromString(arguments.at(i + 1));
             i++;
         }
     }
     const QList<ThemeEntry> availableThemes = ThemeEntry::availableThemes();
     int themeIndex = Utils::indexOf(availableThemes, Utils::equal(&ThemeEntry::id, themeId));
     if (themeIndex < 0) {
         themeIndex = Utils::indexOf(availableThemes,
                                     Utils::equal(&ThemeEntry::id, settingsThemeId));
     }

     if (themeIndex < 0)
         themeIndex = 0;

     if (themeIndex < availableThemes.size()) {
         const ThemeEntry themeEntry = availableThemes.at(themeIndex);
         QSettings themeSettings(themeEntry.filePath(), QSettings::IniFormat);

         Theme *theme = new Theme(themeEntry.id().toString(), qApp);
         theme->readSettings(themeSettings);
         if (theme->flag(Theme::ApplyThemePaletteGlobally))
             QApplication::setPalette(theme->palette());
         setCreatorTheme(theme);
     }

     // defer creation of these widgets until here,
     // because they need a valid theme set
     m_mainWindow = new MainWindow;

     ActionManager::setPresentationModeEnabled(false);

     const bool success = m_mainWindow->init(errorMessage);
     if (success) {
         m_editMode = new EditMode;
         addObject(m_editMode);
         ModeManager::activateMode(m_editMode->id());
//         m_designMode = new DesignMode;
//         InfoBar::initializeGloballySuppressed();
     }

     if (overrideColor.isValid())
         m_mainWindow->setOverrideColor(overrideColor);

    return success;
}

void CorePlugin::extensionsInitialized()
{
//    if (m_designMode->designModeIsRequired())
//        addObject(m_designMode);
    m_mainWindow->extensionsInitialized();
    if (ExtensionSystem::PluginManager::hasError()) {
        auto errorOverview = new ExtensionSystem::PluginErrorOverview(m_mainWindow);
        errorOverview->setAttribute(Qt::WA_DeleteOnClose);
        errorOverview->setModal(true);
        errorOverview->show();
    }
}

bool CorePlugin::delayedInitialize()
{
    m_mainWindow->show ();
    return true;
}

ExtensionSystem::IPlugin::ShutdownFlag CorePlugin::aboutToShutdown()
{
    m_mainWindow->aboutToShutdown ();
    return SynchronousShutdown;
}

void CorePlugin::initStyle()
{
    QFile file( QLatin1String(":/css/core.css") );
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    m_mainWindow->setStyleSheet(styleSheet);
}
