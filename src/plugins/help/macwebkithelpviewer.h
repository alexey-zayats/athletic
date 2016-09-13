#ifndef MACWEBKITHELPVIEWER_H
#define MACWEBKITHELPVIEWER_H

#include "helpviewer.h"

#include <QMacCocoaViewContainer>

Q_FORWARD_DECLARE_OBJC_CLASS(DOMNode);
Q_FORWARD_DECLARE_OBJC_CLASS(DOMRange);
Q_FORWARD_DECLARE_OBJC_CLASS(NSString);
Q_FORWARD_DECLARE_OBJC_CLASS(WebView);

namespace Help {
namespace Internal {

class MacWebKitHelpViewer;
class MacWebKitHelpWidgetPrivate;

class MacResponderHack : public QObject
{
    Q_OBJECT

public:
    MacResponderHack(QObject *parent);

private slots:
    void responderHack(QWidget *old, QWidget *now);
};

class MacWebKitHelpWidget : public QMacCocoaViewContainer
{
    Q_OBJECT

public:
    MacWebKitHelpWidget(MacWebKitHelpViewer *parent);
    ~MacWebKitHelpWidget();

    void setOpenInNewPageActionVisible(bool visible);

    WebView *webView() const;
    void startToolTipTimer(const QPoint &pos, const QString &text);
    void hideToolTip();

protected:
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);

private:
    void showToolTip();
    MacWebKitHelpWidgetPrivate *d;
};

class MacWebKitHelpViewer : public HelpViewer
{
    Q_OBJECT

public:
    explicit MacWebKitHelpViewer(QWidget *parent = 0);
    ~MacWebKitHelpViewer();

    QFont viewerFont() const;
    void setViewerFont(const QFont &font);

    qreal scale() const;
    void setScale(qreal scale);

    QString title() const;

    QUrl source() const;
    void setSource(const QUrl &url);
    void scrollToAnchor(const QString &anchor);
    void highlightId(const QString &id) { Q_UNUSED(id) }

    void setHtml(const QString &html);

    QString selectedText() const;
    bool isForwardAvailable() const;
    bool isBackwardAvailable() const;
    void addBackHistoryItems(QMenu *backMenu);
    void addForwardHistoryItems(QMenu *forwardMenu);
    void setOpenInNewPageActionVisible(bool visible);

    bool findText(const QString &text, Core::FindFlags flags,
        bool incremental, bool fromSearch, bool *wrapped = 0);

    MacWebKitHelpWidget *widget() const { return m_widget; }

public slots:
    void scaleUp();
    void scaleDown();
    void resetScale();
    void copy();
    void stop();
    void forward();
    void backward();
    void print(QPrinter *printer);

public slots:
    void slotLoadStarted();
    void slotLoadFinished();

private slots:
    void goToHistoryItem();

private:
    DOMRange *findText(NSString *text, bool forward, bool caseSensitive, DOMNode *startNode,
                       int startOffset);
    MacWebKitHelpWidget *m_widget;
};

}   // namespace Internal
}   // namespace Help

#endif // MACWEBKITHELPVIEWER_H
