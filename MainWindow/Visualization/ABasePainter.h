#pragma once

#include "../../AlgorithmsModule/IBasePainter.h"
#include "SceneElements/Constants.h"
#include "SceneElements/CRectItem.h"

namespace Visualization
{

    class ABasePainter : IBasePainter
    {
    public:

        explicit ABasePainter(QGraphicsView*);
        void drawBasicScene(const TextsPair&) override;
        void finishScene(const Indices&) override;
        void cleanWholeScene() override;

    protected:

        void drawRectsForText(const std::string&, const Constants::ERectType);
        void colorRects(const std::vector<RectItemPtr>&, const Indices&, const Qt::GlobalColor);
        void clearAllHighlight();

        QGraphicsView* m_view;
        std::vector<RectItemPtr> m_sourceRectItems; //sorted from left to right on screen
        std::vector<RectItemPtr> m_patternRectItems; //sorted from left to right on screen
    };

} // Visualization
