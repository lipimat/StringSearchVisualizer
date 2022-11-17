#pragma once

#include "../../AlgorithmsModule/IControllerToolsetFactory.h"

namespace Algorithms
{

    struct CControllerToolsetFactoryMock final : IControllerToolsetFactory
    {
        //stubs
        std::function<std::string_view()> m_createName;
        std::function<std::string_view()> m_createInfo;
        std::function<StepsExecutorPtr()> m_createStepsExecutor;
        std::function<Visualization::PainterPtr(const Visualization::PainterFactoryPtr&)> m_createPainter;
        //interface functions
        std::string_view createName() const override { return m_createName(); };
        std::string_view createInfo() const override { return m_createInfo(); };
        StepsExecutorPtr createStepsExecutor() const override { return m_createStepsExecutor(); };
        Visualization::PainterPtr createPainter(const Visualization::PainterFactoryPtr& factory) const override
            { return m_createPainter(factory); };
    };

} //Algorithms
