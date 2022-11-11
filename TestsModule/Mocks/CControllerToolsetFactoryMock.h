#pragma once

#include <functional>

#include "../AlgorithmsModule/IControllerToolsetFactory.h"

namespace Algorithms
{

    struct CControllerToolsetFactoryMock final : IControllerToolsetFactory
    {
        //stubs
        std::function<std::string_view()> m_createName;
        std::function<std::string_view()> m_createInfo;
        std::function<std::unique_ptr<IStepsExecutor>()> m_createStepsExecutor;

        //interface functions
        std::string_view createName() const override { return m_createName(); };
        std::string_view createInfo() const override { return m_createInfo(); };
        std::unique_ptr<IStepsExecutor> createStepsExecutor() const override { return m_createStepsExecutor(); };
    };

} //Algorithms
