#pragma once

#include "../AlgorithmsModule/Steps/IStep.h"

namespace Algorithms
{
namespace Steps
{

    class CStepMock final : public IStep
    {
    public:
        void accept(const Window::Visualization::PainterPtr&) const override {};
    };

} //Steps
} //Algorithms
