#ifndef SPORTSGRID_H
#define SPORTSGRID_H

#include "sportbutton.h"

#include <QIcon>
#include <QWidget>

#include <QTimer>

namespace Core {
namespace Internal {

class SportsGrid : public QWidget
{
    Q_OBJECT

public:
    SportsGrid(QWidget *parent = 0);
    ~SportsGrid();

    bool event(QEvent *event);

    void paintEvent(QPaintEvent *event);
    void paintSport(QPainter *painter, int index) const;
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    bool validIndex(int index) const { return index >= 0 && index < m_sports.count(); }

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

    void setSportEnabled(int index, bool enable);
    bool isSportEnabled(int index) const;

    void insertSport(int index, const QIcon &icon, const QString &label) {
        SportButton *sb = new SportButton(this);
        sb->icon = icon;
        sb->text = label;
        m_sports.insert(index, sb);
        updateGeometry();
    }

    void removeSport(int index) {
        SportButton *sb = m_sports.takeAt(index);
        delete sb;
        updateGeometry();
    }
    void setCurrentIndex(int index);
    int currentIndex() const { return m_currentIndex; }

    void setSportToolTip(int index, QString toolTip) { m_sports[index]->toolTip = toolTip; }
    QString sportToolTip(int index) const { return m_sports.at(index)->toolTip; }

    QIcon sportIcon(int index) const { return m_sports.at(index)->icon; }
    QString sportText(int index) const { return m_sports.at(index)->text; }
    int count() const {return m_sports.count(); }
    QRect sportRect(int index) const;

    void setGridSize(int size);

signals:
    void currentChanged(int);

public slots:
    void emitCurrentIndex();

private:
    static const int m_rounding;
    static const int m_textPadding;

    static const int m_colls;

    int m_sportSize;

    QRect m_hoverRect;
    int m_hoverIndex;
    int m_currentIndex;
    QList<SportButton*> m_sports;
    QTimer m_triggerTimer;
    QSize sportSizeHint(bool minimum = false) const;
    QRect m_parentRect;

};

}
}

#endif // SPORTSGRID_H
