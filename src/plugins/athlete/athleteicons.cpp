#include "athleteicons.h"

namespace Athlete
{
namespace Icons
{
const Utils::Icon MODE_ATHLETE_CLASSIC(
        QLatin1String(":/athlete/images/mode_athlete.png"));
const Utils::Icon MODE_ATHLETE_FLAT({
        {QLatin1String(":/athlete/images/mode_athlete_mask.png"), Utils::Theme::IconsBaseColor}});
const Utils::Icon MODE_ATHLETE_FLAT_ACTIVE({
        {QLatin1String(":/athlete/images/mode_athlete_mask.png"), Utils::Theme::IconsModeAthleteActiveColor}});
}

}
