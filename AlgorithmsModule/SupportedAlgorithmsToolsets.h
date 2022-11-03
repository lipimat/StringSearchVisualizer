#pragma once

#include <vector>
#include <memory>

#include "IControllerToolsetFactory.h"
#include "BruteForce/CControllerToolsetFactory.h"

namespace Algorithms
{

    static const std::vector<std::unique_ptr<IControllerToolsetFactory>> toolsetFactories = [] {
        std::vector<std::unique_ptr<IControllerToolsetFactory>> ret;
        ret.push_back(std::make_unique<BruteForce::CControllerToolsetFactory>());
        return ret;
    }();

} //Algorithms
