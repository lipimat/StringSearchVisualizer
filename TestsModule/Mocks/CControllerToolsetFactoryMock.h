#pragma once

#include "../../AlgorithmsModule/IControllerToolsetFactory.h"

namespace Algorithms
{

    template<class Painter>
    struct CControllerToolsetFactoryMock final : IControllerToolsetFactory<Painter>
    {
        //stubs
        std::function<std::string_view()> m_createName;
        std::function<std::string_view()> m_createInfo;
        std::function<StepsExecutorPtr<Painter>()> m_createStepsExecutor;
        //interface functions
        std::string_view createName() const override { return m_createName(); };
        std::string_view createInfo() const override { return m_createInfo(); };
        StepsExecutorPtr<Painter> createStepsExecutor() const override { return m_createStepsExecutor(); };
    };

} //Algorithms
