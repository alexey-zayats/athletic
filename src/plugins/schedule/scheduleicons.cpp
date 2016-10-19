#include "scheduleicons.h"

namespace Schedule
{
namespace Icons
{
const Utils::Icon MODE_SCHEDULE_CLASSIC(
        QLatin1String(":/schedule/images/mode_schedule.png"));
const Utils::Icon MODE_SCHEDULE_FLAT({
        {QLatin1String(":/schedule/images/mode_schedule_mask.png"), Utils::Theme::IconsBaseColor}});
const Utils::Icon MODE_SCHEDULE_FLAT_ACTIVE({
        {QLatin1String(":/schedule/images/mode_schedule_mask.png"), Utils::Theme::IconsModeScheduleActiveColor}});

const Utils::Icon SCHEDULE_GENERAL(
        QLatin1String(":/schedule/images/selector_general.png"));
const Utils::Icon SCHEDULE_BYDAY(
        QLatin1String(":/schedule/images/selector_byday.png"));

const Utils::Icon CALENDAR_SELECTOR(
        QLatin1String(":/schedule/images/calendar.png"));

}
}
