#pragma once

#include "../../AlgorithmsModule/Steps/IStep.h"

namespace Algorithms
{
namespace Steps
{

    template<class Painter>
    class CStepMock final : public IStep<Painter>
    {
    public:
        // stubs
        std::function<void(const Painter&)> m_accept;

        // interface functions
        void accept(const Painter& painter) const override { return m_accept(painter); };
    };

} //Steps
} //Algorithms
