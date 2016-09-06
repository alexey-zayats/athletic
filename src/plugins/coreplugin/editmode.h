#ifndef EDITMODE_H
#define EDITMODE_H

#include <coreplugin/imode.h>

QT_BEGIN_NAMESPACE
class QSplitter;
class QVBoxLayout;
QT_END_NAMESPACE

namespace Core {

class EditorManager;

namespace Internal {

class EditMode : public IMode
{
    Q_OBJECT

public:
    EditMode();
    ~EditMode();

private:
    void grabEditorManager(IMode *mode);

    QSplitter *m_splitter;
    QVBoxLayout *m_rightSplitWidgetLayout;
};

} // namespace Internal
} // namespace Core

#endif // EDITMODE_H
