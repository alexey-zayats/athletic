#ifndef COMPETITIONMODE_H
#define COMPETITIONMODE_H

#include <coreplugin/imode.h>

QT_BEGIN_NAMESPACE
class QSplitter;
class QVBoxLayout;
QT_END_NAMESPACE

namespace Core {
class EditorManager;
}

using namespace Core;

namespace Competition {
namespace Internal {

class CompetitionMode : public IMode
{
    Q_OBJECT

public:
    CompetitionMode();
    ~CompetitionMode();

private:
    void grabEditorManager(IMode *mode);

    QSplitter *m_splitter;
    QVBoxLayout *m_rightSplitWidgetLayout;
};

} // namespace Internal
} // namespace Competition

#endif // COMPETITIONMODE_H