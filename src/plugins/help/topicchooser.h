
#ifndef TOPICCHOOSER_H
#define TOPICCHOOSER_H

#include "ui_topicchooser.h"

#include <QUrl>
#include <QMap>
#include <QModelIndex>
#include <QString>

#include <QDialog>

QT_FORWARD_DECLARE_CLASS(QSortFilterProxyModel)

class TopicChooser : public QDialog
{
    Q_OBJECT

public:
    TopicChooser(QWidget *parent, const QString &keyword,
        const QMap<QString, QUrl> &links);

    QUrl link() const;

private slots:
    void acceptDialog();
    void setFilter(const QString &pattern);
    void activated(const QModelIndex &index);

private:
    bool eventFilter(QObject *object, QEvent *event);

private:
    Ui::TopicChooser ui;
    QList<QUrl> m_links;

    QModelIndex m_activedIndex;
    QSortFilterProxyModel *m_filterModel;
};

#endif // TOPICCHOOSER_H
