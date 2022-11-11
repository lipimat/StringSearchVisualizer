#pragma once

#include "../AlgorithmsModule/IPainter.h"

namespace Window
{
namespace Visualization
{

    class CPainterMock final : public IPainter
    {
        void drawBasicScene(const TextsPair&) override {};
        void cleanWholeScene() override {};
    };

} //Visualization
} //Window
