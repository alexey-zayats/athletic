#include "sportselectorwidget.h"
#include "sportsgrid.h"
#include "sportbutton.h"

#include "../isport.h"
#include "../mainwindow.h"
#include "../tabwidget.h"

#include <utils/styledbar.h>
#include <utils/stylehelper.h>
#include <utils/theme/theme.h>
#include <utils/hostosinfo.h>
#include <utils/icon.h>

#include <coreplugin/icore.h>
#include <coreplugin/actionbar.h>
#include <coreplugin/coreicons.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/modemanager.h>

#include <extensionsystem/pluginmanager.h>

#include <QAction>
#include <QStatusBar>
#include <QPainter>

#include <QDebug>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>

#include <QPixmapCache>
#include <QStackedLayout>
#include <QToolTip>
#include <QApplication>

#include <QToolBar>
#include <QRect>

using namespace Utils;
using namespace ExtensionSystem;

using namespace Core;
using namespace Core::Internal;

static bool lessThanBySporttitle(const ISport *one, const ISport *two)
{
    return one->title() < two->title();
}

SportSelectorWidget::SportSelectorWidget(QAction *sportSelectorAction, QWidget *parent)
    : QWidget(parent),
      m_sportsAction(sportSelectorAction),
      m_sportsGrid(0)
{
    QPalette p;
    p.setColor(QPalette::Foreground, athleticTheme()->color(Theme::MiniProjectTargetSelectorTextColor));
    p.setColor(QPalette::Text, athleticTheme()->color(Theme::MiniProjectTargetSelectorTextColor));
    p.setColor(QPalette::ButtonText, athleticTheme()->color(Theme::MiniProjectTargetSelectorTextColor));
    p.setColor(QPalette::Background, athleticTheme()->color(Theme::MiniProjectTargetSelectorSummaryBackgroundColor));
    p.setColor(QPalette::Base, athleticTheme()->color(Theme::MiniProjectTargetSelectorSummaryBackgroundColor));
    p.setColor(QPalette::Button, athleticTheme()->color(Theme::MiniProjectTargetSelectorSummaryBackgroundColor).name());
    setPalette(p);

    setProperty("panelwidget", true);
    setContentsMargins(QMargins(0, 1, 1, 8));
    setWindowFlags(Qt::Popup);

    m_sportsAction->setIcon(athleticTheme()->flag(Theme::FlatSideBarIcons)
                                      ? Icons::OLYMPIC_FLAT.icon()
                                      : Icons::OLYMPIC_CLASSIC.icon());

    m_sportsAction->setProperty("titledAction", true);
    m_sportsAction->setProperty("heading", tr("Filter"));
    m_sportsAction->setProperty("subtitle", tr("All"));


    QVBoxLayout *layout = new QVBoxLayout(this);

    QList<Core::ISport*> list = PluginManager::getObjects<Core::ISport>();
    qSort(list.begin(), list.end(), lessThanBySporttitle);

    int sportSize = list.size();

    m_sportsGrid = new SportsGrid(this);
    m_sportsGrid->setGridSize(sportSize+1);

    m_sportsGrid->insertSport (0, m_sportsAction->icon (), m_sportsAction->property("subtitle").toString ());
    m_sportsGrid->setSportEnabled (0, true);

    for(int i = 0; i < sportSize; i++) {
        ISport *s = list.at(i);
        m_sportsGrid->insertSport (i+1, s->icon (), s->title ());
        m_sportsGrid->setSportEnabled (i+1, true);
    }

    m_sportsGrid->setCurrentIndex (0);
    connect(m_sportsGrid, &SportsGrid::currentChanged, this, &SportSelectorWidget::sportsChanged);

    layout->addWidget (m_sportsGrid);

    layout->setMargin (0);
    layout->addSpacing(0);
    layout->setMargin(0);
    layout->setSpacing(0);
    setLayout (layout);
    setContentsMargins(0,0,0,0);
}

SportSelectorWidget::~SportSelectorWidget()
{
}

void SportSelectorWidget::sportsChanged (int index)
{
    m_sportsAction->setIcon( m_sportsGrid->sportIcon (index) );
    m_sportsAction->setProperty("subtitle", m_sportsGrid->sportText (index));
    toggleVisible();
}

void SportSelectorWidget::doLayout(bool keepSize)
{
    Q_UNUSED(keepSize)

    static QStatusBar *statusBar = Core::ICore::statusBar();

    QPoint statusPoint = statusBar->mapToGlobal(QPoint(0,0));
    move( statusPoint.x (), statusPoint.y() - /* tabPoint.y () + statusBar->rect ().*/ height ());
}

void SportSelectorWidget::setVisible(bool visible)
{
    doLayout(false);
    QWidget::setVisible(visible);
    m_sportsAction->setChecked(visible);
    if (visible) {
        if (!focusWidget() || !focusWidget()->isVisibleTo(this)) { // Does the second part actually work?
            if (m_sportsGrid->isVisibleTo(this))
                m_sportsGrid->setFocus();
        }
    }
}

void SportSelectorWidget::toggleVisible()
{
    setVisible(!isVisible());
}

void SportSelectorWidget::mousePressEvent(QMouseEvent *e)
{
    setAttribute(Qt::WA_NoMouseReplay);
    QWidget::mousePressEvent(e);
}

void SportSelectorWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(athleticTheme()->color(Theme::MiniProjectTargetSelectorBackgroundColor));
    painter.drawRect(rect());
    painter.setPen(athleticTheme()->color(Theme::MiniProjectTargetSelectorBorderColor));
    // draw border on top and right
    QRectF borderRect = QRectF(rect()).adjusted(0.5, 0.5, -0.5, -0.5);
    painter.drawLine(borderRect.topLeft(), borderRect.topRight());
    painter.drawLine(borderRect.topRight(), borderRect.bottomRight());
}
