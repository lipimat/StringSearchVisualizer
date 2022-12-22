#pragma once

#include "BruteForce/CControllerCreator.h"
#include "BoyerMoore/CControllerCreator.h"
#include "Automaton/CControllerCreator.h"

namespace Algorithms
{

    static const std::vector<ControllerCreatorPtr> SUPPORTED_CONTROLLERS = [] {
        std::vector<ControllerCreatorPtr> ret;
        ret.push_back(std::make_unique<BruteForce::CControllerCreator>());
        ret.push_back(std::make_unique<BoyerMoore::CControllerCreator>());
        ret.push_back(std::make_unique<Automaton::CControllerCreator>());
        return ret;
    }();

} // Algorithms
