#pragma once

#include "IControllerToolsetFactory.h"
#include "BruteForce/CControllerToolsetFactory.h"

namespace Algorithms
{

    static const std::vector<ControllerToolsetFactoryPtr> SUPPORTED_TOOLSETS = [] {
        std::vector<ControllerToolsetFactoryPtr> ret;
        ret.push_back(std::make_unique<BruteForce::CControllerToolsetFactory>());
        return ret;
    }();

} //Algorithms
