#pragma once

#include "../../AlgorithmsModule/BruteForce/IPainter.h"
#include "../../AlgorithmsModule/Automaton/IPainter.h"
#include "../../AlgorithmsModule/Steps/CComparison.h"
#include "../../AlgorithmsModule/Steps/CMovePattern.h"
#include "../../AlgorithmsModule/Steps/CDrawAutomatonNode.h"
#include "../../AlgorithmsModule/Steps/CStartAutomaton.h"
#include "../../AlgorithmsModule/Steps/CStateChangedAutomaton.h"

namespace Visualization
{
class CPainterMock;
using PainterPtr = std::unique_ptr<CPainterMock>;

    // dirty trick, boyermoore has the same methods so we will use only brute force - think about refactoring this mock in some manner
    // i'm lacking time so i'm leaving it that way
    class CPainterMock final : public BruteForce::IPainter/*, public BoyerMoore::IPainter*/, public Automaton::IPainter
    {
    public:
        //stubs
        std::function<void(const TextsPair&)> m_drawBasicScene;
        std::function<void()> m_cleanWholeScene;
        std::function<void(const Algorithms::Steps::CComparison<BruteForce::PainterPtr>*)> m_paintComparison;
        std::function<void(const Algorithms::Steps::CMovePattern<BruteForce::PainterPtr>*)> m_paintMovePattern;
        std::function<void(const Algorithms::Steps::CDrawAutomatonNode<Automaton::PainterPtr>*)> m_drawAutomatonNode;
        std::function<void(const Algorithms::Steps::CStartAutomaton<Automaton::PainterPtr>*)> m_startAutomaton;
        std::function<void(const Algorithms::Steps::CStateChangedAutomaton<Automaton::PainterPtr>*)> m_stateChangedAutomaton;
        std::function<void(const Indices&)> m_finishScene;


        //interface functions
        void drawBasicScene(const TextsPair& texts) override { return m_drawBasicScene(texts); };
        void paint(const Algorithms::Steps::CComparison<BruteForce::PainterPtr>* step) override { return m_paintComparison(step);};
        void paint(const Algorithms::Steps::CMovePattern<BruteForce::PainterPtr>* step) override { return m_paintMovePattern(step); };
        void paint(const Algorithms::Steps::CDrawAutomatonNode<Automaton::PainterPtr>* step) override { return m_drawAutomatonNode(step); };
        void paint(const Algorithms::Steps::CStartAutomaton<Automaton::PainterPtr>* step) override { return m_startAutomaton(step); };
        void paint(const Algorithms::Steps::CStateChangedAutomaton<Automaton::PainterPtr>* step) override { return m_stateChangedAutomaton(step); };
        void finishScene(const Indices& indices) override { return m_finishScene(indices); };
        void cleanWholeScene() override { return m_cleanWholeScene(); };
    };

} //Visualization
