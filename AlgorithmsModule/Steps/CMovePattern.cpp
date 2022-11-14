#include "CMovePattern.h"

namespace Algorithms
{
namespace Steps
{

    void CMovePattern::accept(const Window::Visualization::PainterPtr& painter) const
    {
        painter->movePattern();
    }

} //Steps
} //Algorithms
