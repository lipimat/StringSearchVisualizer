#include "CMovePattern.h"

namespace Algorithms
{
namespace Steps
{

    void CMovePattern::accept(const Visualization::PainterPtr& painter) const
    {
        painter->paint(this);
    }

} //Steps
} //Algorithms
