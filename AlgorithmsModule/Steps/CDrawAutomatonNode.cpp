#include "CDrawAutomatonNode.h"
#include "../Automaton/IPainter.h"

namespace Algorithms
{
namespace Steps
{

    template<class Painter>
    CDrawAutomatonNode<Painter>::CDrawAutomatonNode(const int stateNumber, const NodeRelations& relations)
        : m_stateNumber(stateNumber), m_nodeRelations(relations)
    {
    }

    template<class Painter>
    void  CDrawAutomatonNode<Painter>::accept(const Painter& painter) const
    {
        assert(painter != nullptr);
        painter->paint(this);
    }

    template<class Painter>
    bool  CDrawAutomatonNode<Painter>::operator==(const  CDrawAutomatonNode<Painter>& rhs)
    {
        return this->m_stateNumber == rhs.m_stateNumber &&
               this->m_nodeRelations == rhs.m_nodeRelations;
    }

    template class CDrawAutomatonNode<Visualization::Automaton::PainterPtr>;

} // Steps
} // Algorithms
