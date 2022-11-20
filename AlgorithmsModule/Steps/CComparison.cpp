#include "CComparison.h"

namespace Algorithms
{
namespace Steps
{

    CComparison::CComparison(
            const Indices& sourceIndices,
            const Indices& patternIndices,
            const EComparisonType comparisonType) :
        m_sourceIndices(sourceIndices), m_patternIndices(patternIndices), m_comparisonType(comparisonType)
    {
    }

    void CComparison::accept(const Visualization::PainterPtr& painter) const
    {
        assert(painter != nullptr);
        painter->paint(this);
    }

    bool CComparison::operator==(const CComparison& rhs)
    {
        return
            this->m_comparisonType == rhs.m_comparisonType &&
            this->m_patternIndices == rhs.m_patternIndices &&
            this->m_sourceIndices == rhs.m_sourceIndices;
    }

} //Steps
} //Algorithms
