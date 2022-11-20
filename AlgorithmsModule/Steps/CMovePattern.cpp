#include "CMovePattern.h"

namespace Algorithms
{
namespace Steps
{

    void CMovePattern::accept(const Visualization::PainterPtr& painter) const
    {
        assert(painter != nullptr);
        painter->paint(this);
    }

    bool CMovePattern::operator==(const CMovePattern&)
    {
        return true;
    }

} //Steps
} //Algorithms
