#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <utils/appmainwindow.h>

#include "icontext.h"
#include "icore.h"

#include <QMap>
#include <QColor>

#include <functional>

QT_BEGIN_NAMESPACE
class QSettings;
class QPrinter;
class QToolButton;
QT_END_NAMESPACE

namespace Core {

class StatusBarWidget;
class HelpManager;
class ModeManager;
class NavigationWidget;
class RightPaneWidget;
class SettingsDatabase;
class EditorManager;

namespace Internal {

class TabWidget;
class GeneralSettings;
class ShortcutSettings;
class StatusBarManager;
class VersionDialog;
class WindowSupport;
class SystemSettings;

class MainWindow : public Utils::AppMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

    bool init(QString *errorMessage);
    void extensionsInitialized();
    void aboutToShutdown();

    IContext *contextObject(QWidget *widget);
    void addContextObject(IContext *context);
    void removeContextObject(IContext *context);

    void updateAdditionalContexts(const Context &remove, const Context &add,
                                      ICore::ContextPriority priority);
    inline SettingsDatabase *settingsDatabase() const { return m_settingsDatabase; }
    virtual QPrinter *printer() const;

    IContext * currentContextObject() const;

    QStatusBar *statusBar() const;

    void setOverrideColor(const QColor &color);

    QStringList additionalAboutInformation() const;
    void appendAboutInformation(const QString &line);

    void addPreCloseListener(const std::function<bool()> &listener);
    void setSuppressNavigationWidget(bool suppress);



public slots:
    void exit();
    bool showOptionsDialog(Id page = Id(), QWidget *parent = 0);
    void aboutAthletic();

protected:
    virtual void closeEvent(QCloseEvent *event);

private:
    void updateFocusWidget(QWidget *old, QWidget *now);
    void aboutPlugins();
    void setSidebarVisible(bool visible);
    void destroyVersionDialog();
    void restoreWindowState();

    void setFocusToEditor();

    void updateContextObject(const QList<IContext *> &context);
    void updateContext();

    void readSettings();
    void writeSettings();

    void registerDefaultContainers();
    void registerDefaultActions();

    QStringList m_aboutInformation;
    mutable QPrinter *m_printer;

    ICore *m_coreImpl;

    Context m_highPrioAdditionalContexts;
    Context m_lowPrioAdditionalContexts;

    StatusBarManager *m_statusBarManager;
    HelpManager *m_helpManager;

    NavigationWidget *m_navigationWidget;
    RightPaneWidget *m_rightPaneWidget;

    ModeManager *m_modeManager;
    TabWidget *m_modeStack;

    SettingsDatabase *m_settingsDatabase;
    GeneralSettings *m_generalSettings;
    SystemSettings *m_systemSettings;
    ShortcutSettings *m_shortcutSettings;

    WindowSupport *m_windowSupport;

    VersionDialog *m_versionDialog;

    StatusBarWidget *m_outputView;
    EditorManager *m_editorManager;

    QList<IContext *> m_activeContext;

    QMap<QWidget *, IContext *> m_contextWidgets;

    QAction *m_newAction;
    QAction *m_openAction;
    QAction *m_exitAction;
    QAction *m_optionsAction;
    QAction *m_toggleModeSelectorAction;

    QAction *m_toggleSideBarAction;

    QToolButton *m_toggleSideBarButton;
    QColor m_overrideColor;
    QList<std::function<bool()>> m_preCloseListeners;
};

} // namespace Internal
} // namespace Core

#endif // MAINWINDOW_H
