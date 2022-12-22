#pragma once

#include "../IControllerCreator.h"

namespace Algorithms
{
namespace BoyerMoore
{
    struct CControllerCreator : public IControllerCreator
    {
        ControllerPtr createController(const Visualization::PainterFactoryPtr&) const override;
    };

} // BoyerMoore
} // Algorithms
