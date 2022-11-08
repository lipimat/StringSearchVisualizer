#pragma once

#include <QGraphicsView>

#include "../AlgorithmsModule/IVisualizationPainter.h"

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
        ~CVisualizationPainter() = default;

    private:

        QGraphicsView* m_view;

    };

} // Visualization
} // Window
