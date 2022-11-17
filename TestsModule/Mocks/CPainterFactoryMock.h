#pragma once

#include "../../AlgorithmsModule/IPainterFactory.h"

namespace Visualization
{

    struct CPainterFactoryMock final : IPainterFactory
    {
        //stubs
        std::function<PainterPtr()> m_createBruteForcePainter;

        //interface functions
        PainterPtr createBruteForcePainter() const override { return m_createBruteForcePainter(); };
    };

} //Visualization

