
#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <coreplugin/sidebar.h>

#include <QFutureInterface>
#include <QFutureWatcher>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QHelpSearchEngine;
class QHelpSearchResultWidget;
class QMouseEvent;
class QUrl;
QT_END_NAMESPACE

namespace Help {
namespace Internal {

class SearchSideBarItem : public Core::SideBarItem
{
    Q_OBJECT

public:
    SearchSideBarItem();

    QList<QToolButton *> createToolBarWidgets();

signals:
    void linkActivated(const QUrl &url, const QStringList &searchTerms, bool newPage);
};

class SearchWidget : public QWidget
{
    Q_OBJECT

public:
    SearchWidget();
    ~SearchWidget();

    void zoomIn();
    void zoomOut();
    void resetZoom();


public slots:
    void reindexDocumentation();

signals:
    void linkActivated(const QUrl &link, const QStringList &searchTerms, bool newPage);

protected:
    void showEvent(QShowEvent *event);

private slots:
    void search() const;

    void searchingStarted();
    void searchingFinished(int hits);

    void indexingStarted();
    void indexingFinished();

private:
    bool eventFilter(QObject* o, QEvent *e);
    void contextMenuEvent(QContextMenuEvent *contextMenuEvent);
    QStringList currentSearchTerms() const;

private:
    int zoomCount;

    QFutureWatcher<void> m_watcher;
    QFutureInterface<void> *m_progress;

    QHelpSearchEngine *searchEngine;
    QHelpSearchResultWidget *resultWidget;
};

} // namespace Internal
} // namespace Help

#endif // SEARCHWIDGET_H
