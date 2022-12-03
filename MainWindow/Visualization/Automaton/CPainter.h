#pragma once

#include "../../AlgorithmsModule/IPainter.h"
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
        //find a way to split painter interfaces so we dont have this garbage here
        void paint(const Algorithms::Steps::CComparison*) override
            {assert("I don't know how to draw");};
        void paint(const Algorithms::Steps::CMovePattern*) override
            {assert("I don't know how to draw");};
        void paint(const Algorithms::Steps::CDrawAutomatonNode*) override;
        void paint(const Algorithms::Steps::CStartAutomaton*) override;
        void paint(const Algorithms::Steps::CStateChangedAutomaton*) override;
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
