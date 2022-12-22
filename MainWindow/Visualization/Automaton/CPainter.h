#pragma once

#include "../../AlgorithmsModule/Automaton/IPainter.h"
#include "../../AlgorithmsModule/Steps/CDrawAutomatonNode.h"
#include "../../AlgorithmsModule/Steps/CStartAutomaton.h"
#include "../../AlgorithmsModule/Steps/CStateChangedAutomaton.h"
#include "../Constants.h"
#include "../BruteForce/CRectItem.h"
#include "../Automaton/CEllipseItem.h"

namespace Visualization
{
namespace Automaton
{
    class CPainter final : public IPainter
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

        // strategy possibility when refactoring
        QPainterPath createRightArrow(const int /*fromState*/, const int /*toState*/, const char /*label*/);
        QPainterPath createSelfArrow(const int /*state*/, const char /*label*/);
        QPainterPath createBackwardsArrow(const int /*fromState*/, const int /*toState*/, const char /*label*/);
        bool m_drawBackwardsArrowUp; // will be refactored, I'm lacking time

        QRectF calculateRectForNode(const int /*stateNr*/);
        void drawRectsForText(const std::string&, const Constants::ERectType);
        void colorRects(const std::vector<RectItemPtr>&, const Indices&, const Qt::GlobalColor);
        void clearAllHighlight();

        QGraphicsView* m_view;
        std::vector<RectItemPtr> m_sourceRectItems; //sorted from left to right on screen
        std::vector<RectItemPtr> m_patternRectItems; //sorted from left to right on screen
        std::vector<EllipseItemPtr> m_automaton; //sorted from left to right on the screen
    };

} //BruteForce
} //Visualization
