#include "weightliftingsport.h"
#include "weightliftingicons.h"

using namespace WeightLifting;
using namespace WeightLifting::Internal;
using namespace Core;

WeightLiftingSport::WeightLiftingSport(QObject *parent) :
    ISport(parent)
{
    qCDebug(weightliftingLog) << Q_FUNC_INFO;
}

WeightLiftingSport::~WeightLiftingSport()
{}

QString WeightLiftingSport::title() const
{
    return tr("Weightlifting");
}

int WeightLiftingSport::priority() const
{
    return 1;
}

Core::Id WeightLiftingSport::id() const
{
    return Id("Weightlifting");
}

QIcon WeightLiftingSport::icon() const
{
    return WeightLifting::Icons::MODE_WEIGHTLIFTING.icon ();
}

