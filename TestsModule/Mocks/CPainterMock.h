#pragma once

#include "../../AlgorithmsModule/IPainter.h"

namespace Visualization
{

    class CPainterMock final : public IPainter
    {
    public:
        //stubs
        std::function<void(const TextsPair&)> m_drawBasicScene;
        std::function<void(const Indices&, const Indices&, const Qt::GlobalColor)> m_highlightRects;
        std::function<void()> m_movePattern;
        std::function<void()> m_cleanWholeScene;

        //interface functions
        void drawBasicScene(const TextsPair& texts) override { return m_drawBasicScene(texts); };
        void highlightRects(const Indices& sourceIndices, const Indices& patternIndices, const Qt::GlobalColor color) override
            { return m_highlightRects(sourceIndices, patternIndices, color); };
        void movePattern() override { return m_movePattern(); };
        void cleanWholeScene() override { return m_cleanWholeScene(); };
    };

} //Visualization
