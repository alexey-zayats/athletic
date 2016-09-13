#ifndef DOCSETTINGSPAGE_H
#define DOCSETTINGSPAGE_H

#include "ui_docsettingspage.h"
#include <coreplugin/dialogs/ioptionspage.h>

#include <QList>
#include <QPointer>

QT_FORWARD_DECLARE_CLASS(QSortFilterProxyModel)
QT_FORWARD_DECLARE_CLASS(QModelIndex)

namespace Help {
namespace Internal {

class DocModel;

class DocSettingsPage : public Core::IOptionsPage
{
    Q_OBJECT

public:
    DocSettingsPage();

    QWidget *widget();
    void apply();
    void finish();

private slots:
    void addDocumentation();

private:
    bool eventFilter(QObject *object, QEvent *event);
    void removeDocumentation(const QList<QModelIndex> &items);

private:
    QList<QModelIndex> currentSelection() const;

    Ui::DocSettingsPage m_ui;
    QPointer<QWidget> m_widget;

    QString m_recentDialogPath;

    typedef QHash<QString, QString> NameSpaceToPathHash;
    NameSpaceToPathHash m_filesToRegister;
    QHash<QString, bool> m_filesToRegisterUserManaged;
    NameSpaceToPathHash m_filesToUnregister;

    QSortFilterProxyModel *m_proxyModel = nullptr;
    DocModel *m_model = nullptr;
};

} // namespace Help
} // namespace Internal

#endif // DOCSETTINGSPAGE_H
