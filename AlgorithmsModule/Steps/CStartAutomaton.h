#pragma once

#include "IStep.h"

namespace Algorithms
{
namespace Steps
{

    class CStartAutomaton final : public IStep
    {
    public:
        void accept(const Visualization::PainterPtr&) const override;
    };

} //Steps
} //Algorithms
