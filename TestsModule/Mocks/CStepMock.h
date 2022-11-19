#pragma once

#include "../../AlgorithmsModule/Steps/IStep.h"

namespace Algorithms
{
namespace Steps
{

    class CStepMock final : public IStep
    {
    public:
        // stubs
        std::function<void(const Visualization::PainterPtr&)> m_accept;

        // interface functions
        void accept(const Visualization::PainterPtr& painter) const override { return m_accept(painter); };
    };

} //Steps
} //Algorithms
