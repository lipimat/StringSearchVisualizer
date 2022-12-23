#pragma once

#include "../../AlgorithmsModule/IPainterFactory.h"
#include "../../AlgorithmsModule/BruteForce/IPainter.h"
#include "../../AlgorithmsModule/BoyerMoore/IPainter.h"
#include "../../AlgorithmsModule/Automaton/IPainter.h"

namespace Visualization
{

    struct CPainterFactoryMock final : IPainterFactory
    {
        //stubs
        std::function<BruteForce::PainterPtr()> m_createBruteForcePainter;
        std::function<BoyerMoore::PainterPtr()> m_createBoyerMoorePainter;
        std::function<Automaton::PainterPtr()> m_createAutomatonPainter;

        //interface functions
        BruteForce::PainterPtr createBruteForcePainter() const override { return m_createBruteForcePainter(); };
        BoyerMoore::PainterPtr createBoyerMoorePainter() const override { return m_createBoyerMoorePainter(); };
        Automaton::PainterPtr createAutomatonPainter() const override { return m_createAutomatonPainter(); };
    };

} //Visualization

