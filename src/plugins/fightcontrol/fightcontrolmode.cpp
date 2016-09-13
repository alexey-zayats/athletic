#include "fightcontrolmode.h"

#include <coreplugin/coreconstants.h>
#include <coreplugin/icore.h>
#include <coreplugin/coreicons.h>
#include <coreplugin/modemanager.h>

#include <coreplugin/ifightboard.h>

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

using namespace FightControl;
using namespace FightControl::Internal;

using namespace Core;
using namespace Utils;
using namespace ExtensionSystem;

static const char currentPageSettingsKeyC[] = "MatchTab";

FightControlMode::FightControlMode()
    : m_activePlugin(0)
{
    setDisplayName(tr("Match"));

    const Utils::Icon MODE_MATCH_CLASSIC(
            QLatin1String(":/fightcontrol/images/mode_match.png"));
    const Utils::Icon MODE_MATCH_FLAT({
            {QLatin1String(":/fightcontrol/images/mode_match_mask.png"), Utils::Theme::IconsBaseColor}});
    const Utils::Icon MODE_MATCH_FLAT_ACTIVE({
            {QLatin1String(":/fightcontrol/images/mode_match_mask.png"), Utils::Theme::IconsModeMatchActiveColor}});

    setIcon(Utils::Icon::modeIcon(MODE_MATCH_CLASSIC,
                                  MODE_MATCH_FLAT,
                                  MODE_MATCH_FLAT_ACTIVE));

    setPriority(Constants::P_MODE_MATCH);
    setId(Constants::MODE_MATCH);
    setContext(Context(Constants::C_MATCH_MODE));

    m_modeWidget = new QWidget;
    m_modeWidget->setObjectName(QLatin1String("MatchModeWidget"));
    QVBoxLayout *layout = new QVBoxLayout(m_modeWidget);
    layout->setMargin(0);
    layout->setSpacing(0);

    m_matchPage = new QWidget(m_modeWidget);
    m_matchPage->setObjectName(QLatin1String("Match"));

    StyledBar *styledBar = new StyledBar(m_modeWidget);
    styledBar->setObjectName(QLatin1String("MatchStyledBar"));
    layout->addWidget(styledBar);

    m_modeWidget->setLayout(layout);
    layout->addWidget(m_matchPage);

    setWidget(m_modeWidget);
}

FightControlMode::~FightControlMode()
{
    QSettings *settings = ICore::settings();
    settings->setValue(QLatin1String(currentPageSettingsKeyC), activePlugin());
    delete m_modeWidget;
}

void FightControlMode::initPlugins()
{
    QSettings *settings = ICore::settings();
    setActivePlugin(settings->value(QLatin1String(currentPageSettingsKeyC)).toInt());


    QList<IFightBoard *> availablePages = PluginManager::getObjects<IFightBoard>();
    addPages(availablePages);

    // make sure later added pages are made available too:
    connect(PluginManager::instance(), &PluginManager::objectAdded,
            this, &FightControlMode::pluginAdded);
}

void FightControlMode::pluginAdded(QObject *obj)
{
    IFightBoard *page = qobject_cast<IFightBoard*>(obj);
    if (!page)
        return;
    addPages(QList<IFightBoard *>() << page);
}

void FightControlMode::addPages(const QList<IFightBoard *> &pages)
{
    QList<IFightBoard *> addedPages = pages;
    Utils::sort(addedPages, [](const IFightBoard *l, const IFightBoard *r) {
        return l->priority() < r->priority();
    });

    // insert into m_pluginList, keeping m_pluginList sorted by priority
    auto addIt = addedPages.begin();
    auto currentIt = m_pluginList.begin();
    while (addIt != addedPages.end()) {
        IFightBoard *page = *addIt;
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
