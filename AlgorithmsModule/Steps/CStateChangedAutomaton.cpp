#include "CStateChangedAutomaton.h"

namespace Algorithms
{
namespace Steps
{

    CStateChangedAutomaton::CStateChangedAutomaton(const Indices& sourceIndices, const int stateNr) :
        m_sourceIndices(sourceIndices), m_stateNr(stateNr)
    {
    }

    void CStateChangedAutomaton::accept(const Visualization::PainterPtr& painter) const
    {
        assert(painter != nullptr);
        painter->paint(this);
    }

} //Steps
} //Algorithms
