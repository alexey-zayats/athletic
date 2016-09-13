
#ifndef HELPPLUGIN_H
#define HELPPLUGIN_H

#include "helpwidget.h"

#include <coreplugin/helpmanager.h>
#include <coreplugin/icontext.h>
#include <extensionsystem/iplugin.h>

#include <QMap>
#include <QStringList>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QToolButton;
class QUrl;
QT_END_NAMESPACE

namespace Core {
class IMode;
class MiniSplitter;
class SideBar;
class SideBarItem;
}   // Core

namespace Utils { class StyledBar; }

namespace Help {
namespace Internal {
class CentralWidget;
class DocSettingsPage;
class FilterSettingsPage;
class GeneralSettingsPage;
class HelpMode;
class HelpViewer;
class LocalHelpManager;
class OpenPagesManager;
class SearchWidget;
class SearchTaskHandler;

class HelpPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "cloud.athletic.app.plugin" FILE "help.json")

public:
    HelpPlugin();
    virtual ~HelpPlugin();

    bool initialize(const QStringList &arguments, QString *errorMessage);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

    static HelpViewer *createHelpViewer(qreal zoom);

private slots:
    void modeChanged(Core::IMode *mode, Core::IMode *old);

    void showContextHelp();
    void activateIndex();
    void activateContents();

    void saveExternalWindowSettings();
    void showLinkInHelpMode(const QUrl &source);
    void showLinksInHelpMode(const QMap<QString, QUrl> &links, const QString &key);
    void slotHideRightPane();

    void updateSideBarSource();
    void updateSideBarSource(const QUrl &newUrl);

    void setupHelpEngineIfNeeded();

    void highlightSearchTermsInContextHelp();
    void handleHelpRequest(const QUrl &url, Core::HelpManager::HelpViewerLocation location);

    void slotOpenSupportPage();
    void slotReportBug();

private:
    void resetFilter();
    void activateHelpMode();
    bool canShowHelpSideBySide() const;
    HelpViewer *viewerForHelpViewerLocation(Core::HelpManager::HelpViewerLocation location);
    HelpViewer *viewerForContextHelp();
    HelpWidget *createHelpWidget(const Core::Context &context, HelpWidget::WidgetStyle style);
    void createRightPaneContextViewer();
    HelpViewer *externalHelpViewer();

    void doSetupIfNeeded();

private:
    HelpMode *m_mode;
    CentralWidget *m_centralWidget;
    HelpWidget *m_rightPaneSideBarWidget;

    DocSettingsPage *m_docSettingsPage;
    FilterSettingsPage *m_filterSettingsPage;
    SearchTaskHandler *m_searchTaskHandler;

    bool m_setupNeeded;
    LocalHelpManager *m_helpManager;
    OpenPagesManager *m_openPagesManager;

    QString m_contextHelpHighlightId;

    QPointer<HelpWidget> m_externalWindow;
    QRect m_externalWindowState;
};

} // namespace Internal
} // namespace Help

#endif // HELPPLUGIN_H
