#include "CStartAutomaton.h"

namespace Algorithms
{
namespace Steps
{

    void CStartAutomaton::accept(const Visualization::PainterPtr& painter) const
    {
        assert(painter != nullptr);
        painter->paint(this);
    }

} //Steps
} //Algorithms
