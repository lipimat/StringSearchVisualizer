#pragma once

#include "IStep.h"

namespace Algorithms
{
namespace Steps
{

    class CMovePattern final : public IStep
    {
    public:
        void accept(const Window::Visualization::PainterPtr&) const override;
    };

} //Steps
} //Algorithms
