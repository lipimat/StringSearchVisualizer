#pragma once

#include "IStep.h"
#include "Constants.h"

namespace Algorithms
{
namespace Steps
{

    template<class Painter>
    class CStateChangedAutomaton final : public IStep<Painter>
    {
    public:
        explicit CStateChangedAutomaton(const Indices&, const int);
        void accept(const Painter&) const override;

        const Indices m_sourceIndices;
        const int m_stateNr;
    };

} // Steps
} // Algorithms
