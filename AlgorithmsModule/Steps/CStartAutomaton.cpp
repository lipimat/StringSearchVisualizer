#include "CStartAutomaton.h"
#include "../Automaton/IPainter.h"

namespace Algorithms
{
namespace Steps
{

    template<class Painter>
    void CStartAutomaton<Painter>::accept(const Painter& painter) const
    {
        assert(painter != nullptr);
        painter->paint(this);
    }

    template class CStartAutomaton<Visualization::Automaton::PainterPtr>;

} // Steps
} // Algorithms
