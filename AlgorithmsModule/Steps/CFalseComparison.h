#pragma once

#include "IStep.h"

namespace Algorithms
{
namespace Steps
{

    using Indices = Window::Visualization::Indices;

    class CFalseComparison final : public IStep
    {
    public:
        explicit CFalseComparison(const Indices&, const Indices&);
        void accept(const Window::Visualization::PainterPtr&) const override;

    private:
        const Indices m_sourceIndices;
        const Indices m_patternIndices;
    };

} //Steps
} //Algorithms
