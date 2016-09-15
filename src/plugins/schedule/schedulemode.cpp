#include "schedulemode.h"
#include "scheduleconstants.h"
#include "scheduleicons.h"

#include <coreplugin/coreconstants.h>

#include <coreplugin/icore.h>
#include <coreplugin/coreicons.h>
#include <coreplugin/iwelcomepage.h>
#include <coreplugin/modemanager.h>

#include <extensionsystem/pluginmanager.h>

#include <utils/algorithm.h>
#include <utils/icon.h>
#include <utils/fileutils.h>
#include <utils/hostosinfo.h>
#include <utils/styledbar.h>

#include <utils/theme/theme.h>

#include <QVBoxLayout>
#include <QMessageBox>

#include <QDir>

using namespace Schedule;
using namespace Schedule::Internal;
using namespace Schedule::Constants;
using namespace Schedule::Icons;

using namespace Core;
using namespace Utils;
using namespace ExtensionSystem;

static const char currentPageSettingsKeyC[] = "ScheduleTab";

ScheduleMode::ScheduleMode()
    : m_activePlugin(0)
{
    setDisplayName(tr("Schedule"));

    setIcon(Utils::Icon::modeIcon(MODE_SCHEDULE_CLASSIC,
                                  MODE_SCHEDULE_FLAT,
                                  MODE_SCHEDULE_FLAT_ACTIVE));

    setPriority(P_MODE_SCHEDULE);
    setId(MODE_SCHEDULE);
    setContextHelpId(QLatin1String("Athletic Manual"));
    setContext(Context(C_SCHEDULE_MODE));

    m_modeWidget = new QWidget;
    m_modeWidget->setObjectName(QLatin1String("SchedulePageModeWidget"));
    QVBoxLayout *layout = new QVBoxLayout(m_modeWidget);
    layout->setMargin(0);
    layout->setSpacing(0);

    m_schedulePage = new QWidget(m_modeWidget);
    m_schedulePage->setObjectName(QLatin1String("Schedule"));

    StyledBar *styledBar = new StyledBar(m_modeWidget);
    styledBar->setObjectName(QLatin1String("SchedulePageStyledBar"));
    layout->addWidget(styledBar);

    m_modeWidget->setLayout(layout);
    layout->addWidget(m_schedulePage);

    setWidget(m_modeWidget);
}

ScheduleMode::~ScheduleMode()
{
    QSettings *settings = ICore::settings();
    settings->setValue(QLatin1String(currentPageSettingsKeyC), activePlugin());
    delete m_modeWidget;
}

void ScheduleMode::initPlugins()
{
    QSettings *settings = ICore::settings();
    setActivePlugin(settings->value(QLatin1String(currentPageSettingsKeyC)).toInt());

//    facilitateQml(m_welcomePage->engine());

    QList<IWelcomePage *> availablePages = PluginManager::getObjects<IWelcomePage>();
    addPages(availablePages);
    // make sure later added pages are made available too:
    connect(PluginManager::instance(), &PluginManager::objectAdded,
            this, &ScheduleMode::pluginAdded);

//    QString path = resourcePath() + QLatin1String("/welcomescreen/welcomescreen.qml");

    // finally, load the root page
//    m_welcomePage->setSource(QUrl::fromLocalFile(path));
}

void ScheduleMode::pluginAdded(QObject *obj)
{
    IWelcomePage *page = qobject_cast<IWelcomePage*>(obj);
    if (!page)
        return;
    addPages(QList<IWelcomePage *>() << page);
}

void ScheduleMode::addPages(const QList<IWelcomePage *> &pages)
{
    QList<IWelcomePage *> addedPages = pages;
    Utils::sort(addedPages, [](const IWelcomePage *l, const IWelcomePage *r) {
        return l->priority() < r->priority();
    });

    // insert into m_pluginList, keeping m_pluginList sorted by priority
    auto addIt = addedPages.begin();
    auto currentIt = m_pluginList.begin();
    while (addIt != addedPages.end()) {
        IWelcomePage *page = *addIt;
        while (currentIt != m_pluginList.end() && (*currentIt)->priority() <= page->priority())
            ++currentIt;
        // currentIt is now either end() or a page with higher value
        currentIt = m_pluginList.insert(currentIt, page);
        m_idPageMap.insert(page->id(), page);
//        page->facilitateQml(engine);
        ++currentIt;
        ++addIt;
    }
}
