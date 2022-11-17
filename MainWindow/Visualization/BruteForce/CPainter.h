#pragma once

#include "../../AlgorithmsModule/IPainter.h"
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
        void highlightRects(const Indices&, const Indices&, const Qt::GlobalColor) override;
        void movePattern() override;
        void cleanWholeScene() override;
        ~CPainter();

    private:

        void drawRectsForText(const std::string&, const Constants::ERectType);

        QGraphicsView* m_view;
        std::vector<RectItemPtr> m_sourceRectItems; //sorted from left to right
        std::vector<RectItemPtr> m_patternRectItems; //sorted from left to right
    };

} //BruteForce
} //Visualization
