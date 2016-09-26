#ifndef MATCHCONTROL_H
#define MATCHCONTROL_H

#include <coreplugin/imatchcontrol.h>

using namespace Core;

namespace Wrestling
{

class MatchControl : public IMatchControl
{
public:
    MatchControl();
    ~MatchControl();

    virtual QString title() const;
    virtual int priority() const;
    virtual Core::Id id() const;
};

}
#endif // MATCHCONTROL_H
