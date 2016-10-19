#include "schedulemode.h"
#include "scheduleconstants.h"
#include "scheduleicons.h"
#include "schedulewidget.h"

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

    layout = new QVBoxLayout(m_modeWidget);
    layout->setMargin(0);
    layout->setSpacing(0);


    StyledBar *styledBar = new StyledBar(m_modeWidget);
    layout->addWidget(styledBar);

    setWidget(m_modeWidget);
}

 void ScheduleMode::init()
 {
     m_scheduleWidget = new ScheduleWidget(m_modeWidget);
     m_scheduleWidget->setObjectName(QLatin1String("Schedule"));

     layout->addWidget(m_scheduleWidget, 1);

      m_modeWidget->setLayout(layout);
 }

ScheduleMode::~ScheduleMode()
{
    delete m_modeWidget;
}


