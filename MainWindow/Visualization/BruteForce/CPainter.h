#pragma once

#include "../../AlgorithmsModule/IPainter.h"
#include "../../AlgorithmsModule/Steps/CComparison.h"
#include "../../AlgorithmsModule/Steps/CMovePattern.h"
#include "../Constants.h"
#include "CRectItem.h"

namespace Visualization
{
namespace BruteForce
{
    class CPainter final : public IPainter
    {
    public:

        explicit CPainter(QGraphicsView*);
        void drawBasicScene(const TextsPair&) override;
        void paint(const Algorithms::Steps::CComparison*) override;
        void paint(const Algorithms::Steps::CMovePattern*) override;
        //find a way to split painter interfaces so we dont have this garbage here
        void paint(const Algorithms::Steps::CDrawAutomatonNode*) override { assert("I don't know how to draw"); };
        void paint(const Algorithms::Steps::CStartAutomaton*) override { assert("I don't know how to draw"); };
        void paint(const Algorithms::Steps::CStateChangedAutomaton*) override { assert("I don't know how to draw"); };
        void finishScene(const Indices&) override;
        void cleanWholeScene() override;

    private:

        void drawRectsForText(const std::string&, const Constants::ERectType);
        void colorRects(const std::vector<RectItemPtr>&, const Indices&, const Qt::GlobalColor);
        void clearAllHighlight();

        QGraphicsView* m_view;
        std::vector<RectItemPtr> m_sourceRectItems; //sorted from left to right on screen
        std::vector<RectItemPtr> m_patternRectItems; //sorted from left to right on screen
    };

} //BruteForce
} //Visualization
