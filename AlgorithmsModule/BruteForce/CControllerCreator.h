#pragma once

#include "../IControllerCreator.h"

namespace Algorithms
{
namespace BruteForce
{
    struct CControllerCreator : public IControllerCreator
    {
        ControllerPtr createController(const Visualization::PainterFactoryPtr&) const override;
    };

} // BruteForce
} // Algorithms
