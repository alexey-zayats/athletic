#ifndef OPENPAGESMANAGER_H
#define OPENPAGESMANAGER_H

#include <QObject>

QT_FORWARD_DECLARE_CLASS(QComboBox)
QT_FORWARD_DECLARE_CLASS(QListView)
QT_FORWARD_DECLARE_CLASS(QModelIndex)
QT_FORWARD_DECLARE_CLASS(QPoint)
QT_FORWARD_DECLARE_CLASS(QUrl)
QT_FORWARD_DECLARE_CLASS(QWidget)

namespace Help {
    namespace Internal {

class HelpViewer;
class OpenPagesModel;
class OpenPagesSwitcher;
class OpenPagesWidget;

class OpenPagesManager : public QObject
{
    Q_OBJECT

public:
    OpenPagesManager(QObject *parent = 0);
    ~OpenPagesManager();

    static OpenPagesManager &instance();

    QWidget *openPagesWidget() const;
    QComboBox *openPagesComboBox() const;

    int pageCount() const;
    void setupInitialPages();

public slots:
    HelpViewer *createPage();
    HelpViewer *createPage(const QUrl &url);

    void setCurrentPage(int index);
    void setCurrentPage(const QModelIndex &index);

    void closeCurrentPage();
    void closePage(const QModelIndex &index);
    void closePagesExcept(const QModelIndex &index);

    void gotoNextPage();
    void gotoPreviousPage();

signals:
    void pagesChanged();

private:
    void removePage(int index);
    void showTwicherOrSelectPage() const;

private slots:
    void openPagesContextMenu(const QPoint &point);

private:
    QComboBox *m_comboBox;
    OpenPagesModel *m_model;
    mutable OpenPagesWidget *m_openPagesWidget;
    OpenPagesSwitcher *m_openPagesSwitcher;

    static OpenPagesManager *m_instance;
};

    } // namespace Internal
} // namespace Help

#endif // OPENPAGESMANAGER_H
