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
        painter->paint(this);
    }

} //Steps
} //Algorithms
