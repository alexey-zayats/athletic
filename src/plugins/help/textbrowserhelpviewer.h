
#ifndef TEXTBROWSERHELPVIEWER_H
#define TEXTBROWSERHELPVIEWER_H

#include "centralwidget.h"
#include "helpviewer.h"
#include "openpagesmanager.h"

#include <QTextBrowser>

namespace Help {
namespace Internal {

class TextBrowserHelpWidget;

class TextBrowserHelpViewer : public HelpViewer
{
    Q_OBJECT

public:
    explicit TextBrowserHelpViewer(QWidget *parent = 0);
    ~TextBrowserHelpViewer();

    QFont viewerFont() const;
    void setViewerFont(const QFont &font);

    qreal scale() const;
    void setScale(qreal scale);

    QString title() const;

    QUrl source() const;
    void setSource(const QUrl &url);

    void setHtml(const QString &html);

    QString selectedText() const;
    bool isForwardAvailable() const;
    bool isBackwardAvailable() const;
    void addBackHistoryItems(QMenu *backMenu);
    void addForwardHistoryItems(QMenu *forwardMenu);
    void setOpenInNewPageActionVisible(bool visible);

    bool findText(const QString &text, Core::FindFlags flags,
                  bool incremental, bool fromSearch, bool *wrapped = 0);

public slots:
    void scaleUp();
    void scaleDown();
    void resetScale();
    void copy();
    void stop();
    void forward();
    void backward();
    void print(QPrinter *printer);

private slots:
    void goToHistoryItem();

private:
    TextBrowserHelpWidget *m_textBrowser;
};

class TextBrowserHelpWidget : public QTextBrowser
{
    Q_OBJECT

public:
    TextBrowserHelpWidget(TextBrowserHelpViewer *parent);

    QVariant loadResource(int type, const QUrl &name);

    void scaleUp();
    void scaleDown();

    void setSource(const QUrl &name);

protected:
    void contextMenuEvent(QContextMenuEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
    void wheelEvent(QWheelEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    QString linkAt(const QPoint& pos);
    void openLink(const QUrl &url, bool newPage);

    int zoomCount;
    bool forceFont;
    bool m_openInNewPageActionVisible;
    TextBrowserHelpViewer *m_parent;
    friend class Help::Internal::TextBrowserHelpViewer;
};

}   // namespace Internal
}   // namespace Help

#endif // TEXTBROWSERHELPVIEWER_H
