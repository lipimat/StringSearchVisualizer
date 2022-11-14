#include "CFalseComparison.h"

#include "Constants.h"

namespace Algorithms
{
namespace Steps
{

    CFalseComparison::CFalseComparison(const Indices& sourceIndices, const Indices& patternIndices) :
        m_sourceIndices(sourceIndices), m_patternIndices(patternIndices)
    {
    }

    void CFalseComparison::accept(const Window::Visualization::PainterPtr& painter) const
    {
        painter->highlightRects(m_sourceIndices, m_patternIndices, FALSE_COMPARISON_COLOR);
    }

} //Steps
} //Algorithms
