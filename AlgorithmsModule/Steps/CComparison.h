#pragma once

#include "IStep.h"
#include "Constants.h"

namespace Algorithms
{
namespace Steps
{

    template<class Painter>
    class CComparison final : public IStep<Painter>
    {
    public:

        explicit CComparison(const Indices&, const Indices&, const EComparisonType);
        void accept(const Painter&) const override;
        bool operator==(const CComparison&);

        const Indices m_sourceIndices;
        const Indices m_patternIndices;
        const EComparisonType m_comparisonType;
    };

} // Steps
} // Algorithms
