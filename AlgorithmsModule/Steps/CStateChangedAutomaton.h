#pragma once

#include "IStep.h"

namespace Algorithms
{
namespace Steps
{

    using Indices = Visualization::Indices;

    class CStateChangedAutomaton final : public IStep
    {
    public:
        explicit CStateChangedAutomaton(const Indices&, const int);
        void accept(const Visualization::PainterPtr&) const override;

        const Indices m_sourceIndices;
        const int m_stateNr;
    };

} //Steps
} //Algorithms
