#include "CMovePattern.h"

namespace Algorithms
{
namespace Steps
{

    CMovePattern::CMovePattern(const int moveBy) :
        m_moveBy(moveBy)
    {

    }

    void CMovePattern::accept(const Visualization::PainterPtr& painter) const
    {
        assert(painter != nullptr);
        painter->paint(this);
    }

    bool CMovePattern::operator==(const CMovePattern& rhs)
    {
        return this->m_moveBy == rhs.m_moveBy;
    }

} //Steps
} //Algorithms
