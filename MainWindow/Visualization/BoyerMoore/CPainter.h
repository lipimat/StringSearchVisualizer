#pragma once

#include "../../AlgorithmsModule/BoyerMoore/IPainter.h"
#include "../../AlgorithmsModule/Steps/CComparison.h"
#include "../../AlgorithmsModule/Steps/CMovePattern.h"
#include "../Constants.h"
#include "../BruteForce/CRectItem.h"

namespace Visualization
{
namespace BoyerMoore
{
    class CPainter final : public IPainter
    {
    public:

        explicit CPainter(QGraphicsView*);
        void drawBasicScene(const TextsPair&) override;
        void paint(const Algorithms::Steps::CComparison<PainterPtr>*) override;
        void paint(const Algorithms::Steps::CMovePattern<PainterPtr>*) override;
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

} //BoyerMoore
} //Visualization
