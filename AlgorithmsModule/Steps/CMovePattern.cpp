#include "CMovePattern.h"
#include "../BoyerMoore/IPainter.h"
#include "../BruteForce/IPainter.h"

namespace Algorithms
{
namespace Steps
{

    template<class Painter>
    CMovePattern<Painter>::CMovePattern(const int moveBy) :
        m_moveBy(moveBy)
    {
    }

    template<class Painter>
    void CMovePattern<Painter>::accept(const Painter& painter) const
    {
        assert(painter != nullptr);
        painter->paint(this);
    }

    template<class Painter>
    bool CMovePattern<Painter>::operator==(const CMovePattern<Painter>& rhs)
    {
        return this->m_moveBy == rhs.m_moveBy;
    }

    template class CMovePattern<Visualization::BruteForce::PainterPtr>;
    template class CMovePattern<Visualization::BoyerMoore::PainterPtr>;

} // Steps
} // Algorithms
