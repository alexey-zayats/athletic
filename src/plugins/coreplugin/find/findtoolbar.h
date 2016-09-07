#ifndef FINDTOOLBAR_H
#define FINDTOOLBAR_H

#include "ui_findwidget.h"
#include "currentdocumentfind.h"

#include <coreplugin/id.h>
#include <utils/styledbar.h>

#include <QTimer>

QT_BEGIN_NAMESPACE
class QCheckBox;
QT_END_NAMESPACE

namespace Core {

class FindToolBarPlaceHolder;
class FindPlugin;

namespace Internal {

class OptionsPopup : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsPopup(QWidget *parent);

protected:
    bool event(QEvent *ev);
    bool eventFilter(QObject *obj, QEvent *ev);

private:
    void actionChanged();

    QCheckBox *createCheckboxForCommand(Id id);

    QMap<QAction *, QCheckBox *> m_checkboxMap;
};

class FindToolBar : public Utils::StyledBar
{
    Q_OBJECT

public:
    enum OpenFlag {
        UpdateFocusAndSelect = 0x01,
        UpdateFindScope = 0x02,
        UpdateFindText = 0x04,
        UpdateHighlight = 0x08,
        UpdateAll = 0x0F
    };
    Q_DECLARE_FLAGS(OpenFlags, OpenFlag)

    explicit FindToolBar(FindPlugin *plugin, CurrentDocumentFind *currentDocumentFind);
    ~FindToolBar();

    void readSettings();
    void writeSettings();

    void openFindToolBar(OpenFlags flags = UpdateAll);
    void setUseFakeVim(bool on);

    void setLightColoredIcon(bool lightColored);

public slots:
    void setBackward(bool backward);

protected:
    bool focusNextPrevChild(bool next);
    void resizeEvent(QResizeEvent *event);

private:
    void invokeFindNext();
    void invokeGlobalFindNext();
    void invokeFindPrevious();
    void invokeGlobalFindPrevious();
    void invokeFindStep();
    void invokeReplace();
    void invokeGlobalReplace();
    void invokeReplaceNext();
    void invokeGlobalReplaceNext();
    void invokeReplacePrevious();
    void invokeGlobalReplacePrevious();
    void invokeReplaceStep();
    void invokeReplaceAll();
    void invokeGlobalReplaceAll();
    void invokeResetIncrementalSearch();

    void invokeFindIncremental();
    void invokeFindEnter();
    void invokeReplaceEnter();
    void putSelectionToFindClipboard();
    void updateFromFindClipboard();

    void hideAndResetFocus();
    void openFind(bool focus = true);
    void findNextSelected();
    void findPreviousSelected();
    void updateGlobalActions();
    void updateToolBar();
    void findFlagsChanged();
    void findEditButtonClicked();

    void setCaseSensitive(bool sensitive);
    void setWholeWord(bool wholeOnly);
    void setRegularExpressions(bool regexp);
    void setPreserveCase(bool preserveCase);

    void adaptToCandidate();

    void setFocusToCurrentFindSupport();

    void installEventFilters();
    void invokeClearResults();
    void setFindFlag(FindFlag flag, bool enabled);
    bool hasFindFlag(FindFlag flag);
    FindFlags effectiveFindFlags();
    FindToolBarPlaceHolder *findToolBarPlaceHolder() const;
    bool toolBarHasFocus() const;
    bool canShowAllControls(bool replaceIsVisible) const;
    void acceptCandidateAndMoveToolBar();
    void indicateSearchState(IFindSupport::Result searchState);

    bool eventFilter(QObject *obj, QEvent *event);
    void setFindText(const QString &text);
    QString getFindText();
    QString getReplaceText();
    void selectFindText();
    void updateIcons();
    void updateFlagMenus();

    FindPlugin *m_plugin = nullptr;
    CurrentDocumentFind *m_currentDocumentFind = nullptr;
    Ui::FindWidget m_ui;
    QCompleter *m_findCompleter = nullptr;
    QCompleter *m_replaceCompleter = nullptr;
    QAction *m_goToCurrentFindAction = nullptr;
    QAction *m_findInDocumentAction = nullptr;
    QAction *m_findNextSelectedAction = nullptr;
    QAction *m_findPreviousSelectedAction = nullptr;
    QAction *m_enterFindStringAction = nullptr;
    QAction *m_findNextAction = nullptr;
    QAction *m_findPreviousAction = nullptr;
    QAction *m_replaceAction = nullptr;
    QAction *m_replaceNextAction = nullptr;
    QAction *m_replacePreviousAction = nullptr;
    QAction *m_replaceAllAction = nullptr;
    QAction *m_caseSensitiveAction = nullptr;
    QAction *m_wholeWordAction = nullptr;
    QAction *m_regularExpressionAction = nullptr;
    QAction *m_preserveCaseAction = nullptr;

    QAction *m_localFindNextAction = nullptr;
    QAction *m_localFindPreviousAction = nullptr;
    QAction *m_localReplaceAction = nullptr;
    QAction *m_localReplaceNextAction = nullptr;
    QAction *m_localReplacePreviousAction = nullptr;
    QAction *m_localReplaceAllAction = nullptr;

    FindFlags m_findFlags;

    QTimer m_findIncrementalTimer;
    QTimer m_findStepTimer;
    IFindSupport::Result m_lastResult = IFindSupport::NotYetFound;
    bool m_useFakeVim = false;
    bool m_eventFiltersInstalled = false;
};

} // namespace Internal
} // namespace Core

#endif // FINDTOOLBAR_H
