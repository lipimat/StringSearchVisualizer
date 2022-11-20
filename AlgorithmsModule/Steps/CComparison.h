#pragma once

#include "IStep.h"
#include "Constants.h"

namespace Algorithms
{
namespace Steps
{

    using Indices = Visualization::Indices;

    class CComparison final : public IStep
    {
    public:

        explicit CComparison(const Indices&, const Indices&, const EComparisonType);
        void accept(const Visualization::PainterPtr&) const override;
        bool operator==(const CComparison&);

        const Indices m_sourceIndices;
        const Indices m_patternIndices;
        const EComparisonType m_comparisonType;
    };

} //Steps
} //Algorithms
