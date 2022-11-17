#include "CTrueComparison.h"

#include "Constants.h"

namespace Algorithms
{
namespace Steps
{

    CTrueComparison::CTrueComparison(const Indices& sourceIndices, const Indices& patternIndices) :
        m_sourceIndices(sourceIndices), m_patternIndices(patternIndices)
    {
    }

    void CTrueComparison::accept(const Visualization::PainterPtr& painter) const
    {
        painter->highlightRects(m_sourceIndices, m_patternIndices, TRUE_COMPARISON_COLOR);
    }

} //Steps
} //Algorithms
