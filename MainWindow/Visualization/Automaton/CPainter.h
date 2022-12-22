#pragma once

#include "../../AlgorithmsModule/Automaton/IPainter.h"
#include "../../AlgorithmsModule/Steps/CDrawAutomatonNode.h"
#include "../../AlgorithmsModule/Steps/CStartAutomaton.h"
#include "../../AlgorithmsModule/Steps/CStateChangedAutomaton.h"
#include "../ABasePainter.h"
#include "../SceneElements/CEllipseItem.h"

namespace Visualization
{
namespace Automaton
{
    class CPainter final : public IPainter, public ABasePainter
    {
    public:

        explicit CPainter(QGraphicsView*);
        void drawBasicScene(const TextsPair&) override;
        void paint(const Algorithms::Steps::CDrawAutomatonNode<PainterPtr>*) override;
        void paint(const Algorithms::Steps::CStartAutomaton<PainterPtr>*) override;
        void paint(const Algorithms::Steps::CStateChangedAutomaton<PainterPtr>*) override;
        void finishScene(const Indices&) override;
        void cleanWholeScene() override;

    private:

        void clearAllHighlight();

        // strategy possibility when refactoring
        QPainterPath createRightArrow(const int /*fromState*/, const int /*toState*/, const char /*label*/);
        QPainterPath createSelfArrow(const int /*state*/, const char /*label*/);
        QPainterPath createBackwardsArrow(const int /*fromState*/, const int /*toState*/, const char /*label*/);
        QRectF calculateRectForNode(const int /*stateNr*/);

        bool m_drawBackwardsArrowUp; // will be refactored, I'm lacking time
        std::vector<EllipseItemPtr> m_automaton; //sorted from left to right on the screen
    };

} // Automaton
} // Visualization
