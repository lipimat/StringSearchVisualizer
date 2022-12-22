#include "CComparison.h"
#include "../BoyerMoore/IPainter.h"
#include "../BruteForce/IPainter.h"

namespace Algorithms
{
namespace Steps
{

    template<class Painter>
    CComparison<Painter>::CComparison(
            const Indices& sourceIndices,
            const Indices& patternIndices,
            const EComparisonType comparisonType) :
        m_sourceIndices(sourceIndices), m_patternIndices(patternIndices), m_comparisonType(comparisonType)
    {
    }

    template<class Painter>
    void CComparison<Painter>::accept(const Painter& painter) const
    {
        assert(painter != nullptr);
        painter->paint(this);
    }

    template<class Painter>
    bool CComparison<Painter>::operator==(const CComparison<Painter>& rhs)
    {
        return
            this->m_comparisonType == rhs.m_comparisonType &&
            this->m_patternIndices == rhs.m_patternIndices &&
            this->m_sourceIndices == rhs.m_sourceIndices;
    }

    template class CComparison<Visualization::BruteForce::PainterPtr>;
    template class CComparison<Visualization::BoyerMoore::PainterPtr>;

} // Steps
} // Algorithms
