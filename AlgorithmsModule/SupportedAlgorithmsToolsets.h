#pragma once

#include "IControllerToolsetFactory.h"
#include "Automaton/CControllerToolsetFactory.h"
#include "BruteForce/CControllerToolsetFactory.h"
#include "BoyerMoore/CControllerToolsetFactory.h"

namespace Algorithms
{

    static const std::vector<ControllerToolsetFactoryPtr> SUPPORTED_TOOLSETS = [] {
        std::vector<ControllerToolsetFactoryPtr> ret;
        ret.push_back(std::make_unique<BruteForce::CControllerToolsetFactory>());
        ret.push_back(std::make_unique<BoyerMoore::CControllerToolsetFactory>());
        ret.push_back(std::make_unique<Automaton::CControllerToolsetFactory>());
        return ret;
    }();

    static constexpr std::string_view SUPPORTED_ALPHABET = "ACGT";

} //Algorithms
