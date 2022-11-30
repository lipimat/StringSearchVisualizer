#include "CDrawAutomatonNode.h"

namespace Algorithms
{
namespace Steps
{

    CDrawAutomatonNode::CDrawAutomatonNode(const int stateNumber, const NodeRelations& relations)
        : m_stateNumber(stateNumber), m_nodeRelations(relations)
    {
    }

    void CDrawAutomatonNode::accept(const Visualization::PainterPtr& painter) const
    {
        assert(painter != nullptr);
        painter->paint(this);
    }
    bool CDrawAutomatonNode::operator==(const CDrawAutomatonNode& rhs)
    {
        return this->m_stateNumber == rhs.m_stateNumber &&
               this->m_nodeRelations == rhs.m_nodeRelations;
    }

} //Steps
} //Algorithms
