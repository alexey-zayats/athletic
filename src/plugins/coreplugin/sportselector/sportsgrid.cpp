#include "sportsgrid.h"

#include "../actionbar.h"
#include "../core_global.h"

#include <utils/styledbar.h>
#include <utils/stylehelper.h>
#include <utils/theme/theme.h>
#include <utils/hostosinfo.h>

#include <QStyleFactory>
#include <QToolTip>
#include <QHelpEvent>
#include <QPixmapCache>
#include <QPainter>

#include <QtMath>

using namespace Utils;

using namespace Core;
using namespace Core::Internal;

const int SportsGrid::m_rounding = 28;
const int SportsGrid::m_textPadding = 6;
const int SportsGrid::m_colls = 4;

SportsGrid::SportsGrid(QWidget *parent)
    : QWidget(parent)
{
    m_hoverIndex = -1;
    m_currentIndex = -1;
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    setStyle(QStyleFactory::create(QLatin1String("windows")));
    setMinimumWidth(qMax(2 * m_rounding, 40));
    setAttribute(Qt::WA_Hover, true);
    setFocusPolicy(Qt::NoFocus);
    setMouseTracking(true); // Needed for hover events

    m_parentRect = parent->rect ();

    m_triggerTimer.setSingleShot(true);

    // We use a zerotimer to keep the sidebar responsive
    connect(&m_triggerTimer, &QTimer::timeout, this, &SportsGrid::emitCurrentIndex);

    setStyleSheet ( QLatin1String("border: 1px solid blue;") );
}

SportsGrid::~SportsGrid()
{
    delete style();
}

QSize SportsGrid::sportSizeHint(bool minimum) const
{
    QFont boldFont(font());
    boldFont.setPointSizeF(StyleHelper::sidebarFontSize());
    boldFont.setBold(true);
    QFontMetrics fm(boldFont);
    int spacing = 8;
    int width = 60 + spacing + 2;
    int maxLabelwidth = 0;
    for (int sport=0 ; sport<count() ;++sport) {
        int width = fm.width(sportText(sport));
        if (width > maxLabelwidth)
            maxLabelwidth = width;
    }
    int iconHeight = minimum ? 0 : 38;
    return QSize(qMax(width, maxLabelwidth + 4), iconHeight + spacing + fm.height());
}

void SportsGrid::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    if (athleticTheme()->widgetStyle() == Theme::StyleFlat) {
        p.fillRect(event->rect(), StyleHelper::baseColor());
    }

    for (int i = 0; i < count(); ++i)
        if (i != currentIndex())
            paintSport(&p, i);

    // paint active tab last, since it overlaps the neighbors
    if (currentIndex() != -1)
        paintSport(&p, currentIndex());
}

// Handle hover events for mouse fade ins
void SportsGrid::mouseMoveEvent(QMouseEvent *e)
{
    int newHover = -1;
    for (int i = 0; i < count(); ++i) {
        QRect area = sportRect(i);
        if (area.contains(e->pos())) {
            newHover = i;
            break;
        }
    }
    if (newHover == m_hoverIndex)
        return;

    if (validIndex(m_hoverIndex))
        m_sports[m_hoverIndex]->fadeOut();

    m_hoverIndex = newHover;

    if (validIndex(m_hoverIndex)) {
        m_sports[m_hoverIndex]->fadeIn();
        m_hoverRect = sportRect(m_hoverIndex);
    }
}

bool SportsGrid::event(QEvent *event)
{
    if (event->type() == QEvent::ToolTip) {
        if (validIndex(m_hoverIndex)) {
            QString tt = sportToolTip(m_hoverIndex);
            if (!tt.isEmpty()) {
                QToolTip::showText(static_cast<QHelpEvent*>(event)->globalPos(), tt, this);
                return true;
            }
        }
    }
    return QWidget::event(event);
}

// Resets hover animation on mouse enter
void SportsGrid::enterEvent(QEvent *e)
{
    Q_UNUSED(e)
    m_hoverRect = QRect();
    m_hoverIndex = -1;
}

// Resets hover animation on mouse enter
void SportsGrid::leaveEvent(QEvent *e)
{
    Q_UNUSED(e)
    m_hoverIndex = -1;
    m_hoverRect = QRect();
    for (int i = 0 ; i < m_sports.count() ; ++i) {
        m_sports[i]->fadeOut();
    }
}

QSize SportsGrid::sizeHint() const
{
    QSize sh = sportSizeHint();
    return QSize(sh.width() * m_colls, sh.height() * qCeil(m_sportSize / m_colls) );
}

QSize SportsGrid::minimumSizeHint() const
{
    QSize sh = sportSizeHint(true);
    return QSize(sh.width() * m_colls, sh.height() * qCeil(m_sportSize / m_colls) );
}

void SportsGrid::setGridSize(int size) {

    m_sportSize = size;
    QSize sh = sportSizeHint();

    int x = sh.width() * m_colls;
    int y = sh.height() * ((m_sportSize % m_colls) == 0 ? (m_sportSize / m_colls) : (qCeil(m_sportSize / m_colls)+1));

    qDebug() << sh;
    qDebug() << m_sportSize;
    qDebug() << x << y;

    parentWidget ()->resize (QSize(x,y+10));
}

QRect SportsGrid::sportRect(int index) const
{
    QSize sh = sportSizeHint();

    int k = qFloor(index / m_colls);
    int y = k * sh.height();

    int z = (index % m_colls) == 0 ? 0 : ( index - (k * m_colls ) );
    int x = z * sh.width();

    return QRect(x, y, sh.width(), sh.height());

}

void SportsGrid::emitCurrentIndex()
{
    emit currentChanged(m_currentIndex);
}

void SportsGrid::mousePressEvent(QMouseEvent *e)
{
    e->accept();
    for (int index = 0; index < m_sports.count(); ++index) {
        if (sportRect(index).contains(e->pos())) {

            if (isSportEnabled(index)) {
                m_currentIndex = index;
                update();
                m_triggerTimer.start(0);
            }
            break;
        }
    }
}

static void paintSelectedBackground(QPainter *painter, const QRect &spanRect)
{
    const int verticalOverlap = 2; // Grows up and down for the overlaps
    const int dpr = painter->device()->devicePixelRatio();
    const QString cacheKey = QLatin1String(Q_FUNC_INFO) + QString::number(spanRect.width())
            + QLatin1Char('x') + QString::number(spanRect.height())
            + QLatin1Char('@') + QString::number(dpr);
    QPixmap selection;
    if (!QPixmapCache::find(cacheKey, &selection)) {
        selection = QPixmap(QSize(spanRect.width(), spanRect.height() + 2 * verticalOverlap) * dpr);
        selection.fill(Qt::transparent);
        selection.setDevicePixelRatio(dpr);
        QPainter p(&selection);
        p.translate(QPoint(0, verticalOverlap));

        const QRect rect(QPoint(), spanRect.size());
        const QRectF borderRect = QRectF(rect).adjusted(0.5, 0.5, -0.5, -0.5);

        //background
        p.save();
        QLinearGradient grad(rect.topLeft(), rect.topRight());
        grad.setColorAt(0, QColor(255, 255, 255, 140));
        grad.setColorAt(1, QColor(255, 255, 255, 210));
        p.fillRect(rect, grad);
        p.restore();

        //shadows
        p.setPen(QColor(0, 0, 0, 110));
        p.drawLine(borderRect.topLeft() + QPointF(1, -1), borderRect.topRight() - QPointF(0, 1));
        p.drawLine(borderRect.bottomLeft(), borderRect.bottomRight());
        p.setPen(QColor(0, 0, 0, 40));
        p.drawLine(borderRect.topLeft(), borderRect.bottomLeft());

        //highlights
        p.setPen(QColor(255, 255, 255, 50));
        p.drawLine(borderRect.topLeft() + QPointF(0, -2), borderRect.topRight() - QPointF(0, 2));
        p.drawLine(borderRect.bottomLeft() + QPointF(0, 1), borderRect.bottomRight() + QPointF(0, 1));
        p.setPen(QColor(255, 255, 255, 40));
        p.drawLine(borderRect.topLeft() + QPointF(0, 0), borderRect.topRight());
        p.drawLine(borderRect.topRight() + QPointF(0, 1), borderRect.bottomRight() - QPointF(0, 1));
        p.drawLine(borderRect.bottomLeft() + QPointF(0, -1), borderRect.bottomRight() - QPointF(0, 1));

        QPixmapCache::insert(cacheKey, selection);
    }
    painter->drawPixmap(spanRect.topLeft() + QPoint(0, -verticalOverlap), selection);
}

void SportsGrid::paintSport(QPainter *painter, int index) const
{
    if (!validIndex(index)) {
        qWarning("invalid index");
        return;
    }
    painter->save();

    QRect rect = sportRect(index);
    bool selected = (index == m_currentIndex);
    bool enabled = isSportEnabled(index);

    if (selected) {
        if (athleticTheme()->widgetStyle() == Theme::StyleFlat) {
            // background color of a fancy tab that is active
            painter->fillRect(rect, athleticTheme()->color(Theme::ToolButtonSelectedColor));
        } else {
            paintSelectedBackground(painter, rect);
        }
    }

    QString sportText(this->sportText(index));
    QRect sportTextRect(rect);
    const bool drawIcon = rect.height() > 36;
    QRect sportIconRect(sportTextRect);
    sportTextRect.translate(0, drawIcon ? -2 : 1);
    QFont boldFont(painter->font());
    boldFont.setPointSizeF(StyleHelper::sidebarFontSize());
    boldFont.setBold(true);
    painter->setFont(boldFont);
    painter->setPen(selected ? QColor(255, 255, 255, 160) : QColor(0, 0, 0, 110));
    const int textFlags = Qt::AlignCenter | (drawIcon ? Qt::AlignBottom : Qt::AlignVCenter) | Qt::TextWordWrap;

    const float fader = m_sports[index]->fader();
    if (fader > 0 && !HostOsInfo::isMacHost() && !selected && enabled) {
        painter->save();
        painter->setOpacity(fader);
        if (athleticTheme()->widgetStyle() == Theme::StyleFlat)
            painter->fillRect(rect, athleticTheme()->color(Theme::ToolButtonHoverColor));
        else
            ToolButton::hoverOverlay(painter, rect);
        painter->restore();
    }

    if (!enabled && athleticTheme()->widgetStyle() == Theme::StyleDefault)
        painter->setOpacity(0.7);

    if (drawIcon) {
        int textHeight = painter->fontMetrics().boundingRect(QRect(0, 0, width(), height()), Qt::TextWordWrap, sportText).height();
        sportIconRect.adjust(0, 4, 0, -textHeight);
        const QIcon::Mode iconMode = enabled ? (selected ? QIcon::Active : QIcon::Normal)
                                             : QIcon::Disabled;
        StyleHelper::drawIconWithShadow(sportIcon(index), sportIconRect, painter, iconMode);
    }

    painter->setOpacity(1.0); //FIXME: was 0.7 before?
    if (enabled) {
        painter->setPen(selected
                  ? athleticTheme()->color(Theme::TabWidgetEnabledSelectedTextColor)
                  : athleticTheme()->color(Theme::TabWidgetEnabledUnselectedTextColor));
    } else {
        painter->setPen(selected
                        ? athleticTheme()->color(Theme::TabWidgetDisabledSelectedTextColor)
                        : athleticTheme()->color(Theme::TabWidgetDisabledUnselectedTextColor));
    }
    painter->translate(0, -1);
    painter->drawText(sportTextRect, textFlags, sportText);

    painter->restore();
}

void SportsGrid::setCurrentIndex(int index)
{
    if (isSportEnabled(index)) {
        m_currentIndex = index;
        update();
        emit currentChanged(m_currentIndex);
    }
}

void SportsGrid::setSportEnabled(int index, bool enable)
{
    Q_ASSERT(index < m_sports.size());
    Q_ASSERT(index >= 0);

    if (index < m_sports.size() && index >= 0) {
        m_sports[index]->enabled = enable;
        update(sportRect(index));
    }
}

bool SportsGrid::isSportEnabled(int index) const
{
    Q_ASSERT(index < m_sports.size());
    Q_ASSERT(index >= 0);

    if (index < m_sports.size() && index >= 0)
        return m_sports[index]->enabled;

    return false;
}
