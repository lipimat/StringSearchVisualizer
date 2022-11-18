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
