#pragma once

#include <QGraphicsView>

#include "../AlgorithmsModule/IVisualizationPainter.h"
#include "CRectItem.h"
#include "VisualizationConstants.h"

namespace Window
{
namespace Visualization
{

    class CVisualizationPainter final : public IVisualizationPainter
    {
    public:

        CVisualizationPainter(QGraphicsView*);
        void drawBasicScene(const TextsPair&) override;
        void cleanWholeScene() override;
        virtual ~CVisualizationPainter() = default;

    private:

        void drawRectsForText(const std::string&, const Constants::ERectType);

        QGraphicsView* m_view;
        std::vector<RectItemPtr> m_sourceRectItems; //sorted from left to right
        std::vector<RectItemPtr> m_patternRectItems; //sorted from left to right
    };

} // Visualization
} // Window
