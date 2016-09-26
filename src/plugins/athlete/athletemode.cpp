#include "athletemode.h"
#include "athleteicons.h"
#include "athleteconstants.h"

#include <coreplugin/coreconstants.h>
#include <coreplugin/icore.h>

#include <coreplugin/modemanager.h>

#include <coreplugin/imatchboard.h>

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

using namespace Athlete;
using namespace Athlete::Constants;
using namespace Athlete::Internal;
using namespace Athlete::Icons;

using namespace Core;
using namespace Utils;
using namespace ExtensionSystem;

static const char currentPageSettingsKeyC[] = "AthleteTab";

AthleteMode::AthleteMode()
    : m_activePlugin(0)
{
    setDisplayName(tr("Athlete"));

    setIcon(Utils::Icon::modeIcon(MODE_ATHLETE_CLASSIC,
                                  MODE_ATHLETE_FLAT,
                                  MODE_ATHLETE_FLAT_ACTIVE));

    setPriority(Constants::P_MODE_ATHLETE);
    setId(Constants::MODE_ATHLETE);
    setContext(Context(Constants::C_ATHLETE_MODE));

    m_modeWidget = new QWidget;
    m_modeWidget->setObjectName(QLatin1String("AthleteModeWidget"));
    QVBoxLayout *layout = new QVBoxLayout(m_modeWidget);
    layout->setMargin(0);
    layout->setSpacing(0);

    m_matchPage = new QWidget(m_modeWidget);
    m_matchPage->setObjectName(QLatin1String("Athlete"));

    StyledBar *styledBar = new StyledBar(m_modeWidget);
    styledBar->setObjectName(QLatin1String("AthleteStyledBar"));
    layout->addWidget(styledBar);

    m_modeWidget->setLayout(layout);
    layout->addWidget(m_matchPage);

    setWidget(m_modeWidget);
}

AthleteMode::~AthleteMode()
{
    QSettings *settings = ICore::settings();
    settings->setValue(QLatin1String(currentPageSettingsKeyC), activePlugin());
    delete m_modeWidget;
}

void AthleteMode::initPlugins()
{
    QSettings *settings = ICore::settings();
    setActivePlugin(settings->value(QLatin1String(currentPageSettingsKeyC)).toInt());


    QList<IMatchBoard *> availablePages = PluginManager::getObjects<IMatchBoard>();
    addPages(availablePages);

    // make sure later added pages are made available too:
    connect(PluginManager::instance(), &PluginManager::objectAdded,
            this, &AthleteMode::pluginAdded);
}

void AthleteMode::pluginAdded(QObject *obj)
{
    IMatchBoard *page = qobject_cast<IMatchBoard*>(obj);
    if (!page)
        return;
    addPages(QList<IMatchBoard *>() << page);
}

void AthleteMode::addPages(const QList<IMatchBoard *> &pages)
{
    QList<IMatchBoard *> addedPages = pages;
    Utils::sort(addedPages, [](const IMatchBoard *l, const IMatchBoard *r) {
        return l->priority() < r->priority();
    });

    // insert into m_pluginList, keeping m_pluginList sorted by priority
    auto addIt = addedPages.begin();
    auto currentIt = m_pluginList.begin();
    while (addIt != addedPages.end()) {
        IMatchBoard *page = *addIt;
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
