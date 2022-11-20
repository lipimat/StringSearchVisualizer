#pragma once

#include "../../AlgorithmsModule/IPainter.h"
#include "../../AlgorithmsModule/Steps/CComparison.h"
#include "../../AlgorithmsModule/Steps/CMovePattern.h"

namespace Visualization
{

    class CPainterMock final : public IPainter
    {
    public:
        //stubs
        std::function<void(const TextsPair&)> m_drawBasicScene;
        std::function<void()> m_cleanWholeScene;
        std::function<void(const Algorithms::Steps::CComparison*)> m_paintComparison;
        std::function<void(const Algorithms::Steps::CMovePattern*)> m_paintMovePattern;
        std::function<void(const Indices&)> m_finishScene;


        //interface functions
        void drawBasicScene(const TextsPair& texts) override { return m_drawBasicScene(texts); };
        void paint(const Algorithms::Steps::CComparison* step) override { return m_paintComparison(step);};
        void paint(const Algorithms::Steps::CMovePattern* step) override { return m_paintMovePattern(step); };
        void finishScene(const Indices& indices) override { return m_finishScene(indices); };
        void cleanWholeScene() override { return m_cleanWholeScene(); };
    };

} //Visualization
