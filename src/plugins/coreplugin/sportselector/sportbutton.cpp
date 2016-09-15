#include "sportbutton.h"

using namespace Core;
using namespace Core::Internal;

void SportButton::fadeIn()
{
    animator.stop();
    animator.setDuration(80);
    animator.setEndValue(1);
    animator.start();
}

void SportButton::fadeOut()
{
    animator.stop();
    animator.setDuration(160);
    animator.setEndValue(0);
    animator.start();
}

void SportButton::setFader(float value)
{
    m_fader = value;
    m_sportsGrid->update();
}
