
#include "competitionmode.h"
#include "competitionicons.h"
#include "competitionconstants.h"

#include <coreplugin/coreconstants.h>
#include <coreplugin/icore.h>
#include <coreplugin/modemanager.h>
#include <coreplugin/minisplitter.h>
#include <coreplugin/navigationwidget.h>
#include <coreplugin/outputpane.h>
#include <coreplugin/rightpane.h>

//#include <coreplugin/editormanager/editormanager.h>
//#include <coreplugin/editormanager/ieditor.h>

#include <QLatin1String>
#include <QHBoxLayout>
#include <QWidget>
#include <QIcon>

using namespace Competition::Constants;
using namespace Competition::Icons;
using namespace Core;

namespace Competition {
namespace Internal {

CompetitionMode::CompetitionMode() :
    m_splitter(new MiniSplitter),
    m_rightSplitWidgetLayout(new QVBoxLayout)
{
    setObjectName(QLatin1String("CompetitionMode"));
    setDisplayName(tr("Competition"));
    setIcon(Utils::Icon::modeIcon(MODE_COMPETITION_CLASSIC,
                                  MODE_COMPETITION_FLAT,
                                  MODE_COMPETITION_FLAT_ACTIVE));

    setPriority(P_MODE_COMPETITION);
    setId(MODE_COMPETITION);
    setContext(Context(C_COMPETITION_MODE));

    m_rightSplitWidgetLayout->setSpacing(0);
    m_rightSplitWidgetLayout->setMargin(0);

    QWidget *rightSplitWidget = new QWidget;
    rightSplitWidget->setLayout(m_rightSplitWidgetLayout);

    m_rightSplitWidgetLayout->insertWidget(0, new QWidget);

    MiniSplitter *rightPaneSplitter = new MiniSplitter;
    rightPaneSplitter->insertWidget(0, rightSplitWidget);
    rightPaneSplitter->insertWidget(1, new RightPanePlaceHolder(this));
    rightPaneSplitter->setStretchFactor(0, 1);
    rightPaneSplitter->setStretchFactor(1, 0);

    MiniSplitter *splitter = new MiniSplitter;
    splitter->setOrientation(Qt::Vertical);
    splitter->insertWidget(0, rightPaneSplitter);

    m_splitter->insertWidget(0, new NavigationWidgetPlaceHolder(this));
    m_splitter->insertWidget(1, splitter);
    m_splitter->setStretchFactor(0, 0);
    m_splitter->setStretchFactor(1, 1);

    setWidget(m_splitter);
    setContext(Context(Competition::Constants::C_COMPETITION_MODE,
                       Core::Constants::C_NAVIGATION_PANE));
}

CompetitionMode::~CompetitionMode()
{
    delete m_splitter;
}


} // namespace Internal
} // namespace Core
