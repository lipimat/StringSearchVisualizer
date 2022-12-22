#include "CStateChangedAutomaton.h"
#include "../Automaton/IPainter.h"

namespace Algorithms
{
namespace Steps
{

    template<class Painter>
    CStateChangedAutomaton<Painter>::CStateChangedAutomaton(const Indices& sourceIndices, const int stateNr) :
        m_sourceIndices(sourceIndices), m_stateNr(stateNr)
    {
    }

    template<class Painter>
    void CStateChangedAutomaton<Painter>::accept(const Painter& painter) const
    {
        assert(painter != nullptr);
        painter->paint(this);
    }

    template class CStateChangedAutomaton<Visualization::Automaton::PainterPtr>;

} // Steps
} // Algorithms
