#pragma once

#include "../IControllerCreator.h"

namespace Algorithms
{
namespace Automaton
{
    struct CControllerCreator : public IControllerCreator
    {
        ControllerPtr createController(const Visualization::PainterFactoryPtr&) const override;
    };

} // Automaton
} // Algorithms
