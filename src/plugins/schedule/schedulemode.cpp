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
#include <QToolButton>
#include <QHBoxLayout>
#include <QAction>
#include <QSpacerItem>
#include <QButtonGroup>

using namespace Schedule;
using namespace Schedule::Internal;
using namespace Schedule::Constants;
using namespace Schedule::Icons;

using namespace Core;
using namespace Utils;
using namespace ExtensionSystem;

static const char currentPageSettingsKeyC[] = "ScheduleTab";

ScheduleMode::ScheduleMode()
    : m_generalButton(0),
      m_byDayButton(0)
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

    QHBoxLayout *topBarLayout = new QHBoxLayout;
    topBarLayout->setMargin (0);
    topBarLayout->setSpacing (0);
    styledBar->setLayout (topBarLayout);

    QSpacerItem *spacerItem = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Minimum);

    m_generalButton = new QToolButton(styledBar);
    m_generalAction = new QAction(Icons::SCHEDULE_GENERAL.icon (), tr("General"), styledBar);
    m_generalButton->setText ( m_generalAction->text () );
    m_generalButton->setDefaultAction (m_generalAction);

    m_byDayButton = new QToolButton(styledBar);
    m_dayAction = new QAction(Icons::SCHEDULE_BYDAY.icon (), tr("By day"), styledBar);
    m_byDayButton->setText ( m_dayAction->text () );
    m_byDayButton->setDefaultAction (m_dayAction);

    topBarLayout->addWidget (m_generalButton);
    topBarLayout->addWidget (m_byDayButton);
    topBarLayout->addItem (spacerItem);

    layout->addWidget(styledBar);

    m_modeWidget->setLayout(layout);
    layout->addWidget(m_schedulePage);

    setWidget(m_modeWidget);
}

ScheduleMode::~ScheduleMode()
{
    delete m_modeWidget;
}


