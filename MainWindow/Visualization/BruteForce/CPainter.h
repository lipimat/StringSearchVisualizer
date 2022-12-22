#pragma once

#include "../../AlgorithmsModule/BruteForce/IPainter.h"
#include "../../AlgorithmsModule/Steps/CComparison.h"
#include "../../AlgorithmsModule/Steps/CMovePattern.h"
#include "../ABasePainter.h"

namespace Visualization
{
namespace BruteForce
{
    class CPainter final : public IPainter, public ABasePainter
    {
    public:

        explicit CPainter(QGraphicsView*);
        void drawBasicScene(const TextsPair&) override;
        void paint(const Algorithms::Steps::CComparison<PainterPtr>*) override;
        void paint(const Algorithms::Steps::CMovePattern<PainterPtr>*) override;
        void finishScene(const Indices&) override;
        void cleanWholeScene() override;

    };

} // BruteForce
} // Visualization
