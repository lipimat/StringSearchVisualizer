#pragma once

#include <QGraphicsView>

#include "../AlgorithmsModule/IPainter.h"
#include "CRectItem.h"
#include "Constants.h"

namespace Window
{
namespace Visualization
{

    class CPainter final : public IPainter
    {
    public:

        explicit CPainter(QGraphicsView*);
        void drawBasicScene(const TextsPair&) override;
        void cleanWholeScene() override;
        ~CPainter();

    private:

        void drawRectsForText(const std::string&, const Constants::ERectType);

        QGraphicsView* m_view;
        std::vector<RectItemPtr> m_sourceRectItems; //sorted from left to right
        std::vector<RectItemPtr> m_patternRectItems; //sorted from left to right
    };

} // Visualization
} // Window
