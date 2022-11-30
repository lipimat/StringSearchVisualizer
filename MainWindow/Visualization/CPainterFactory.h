#pragma once

#include "../AlgorithmsModule/IPainterFactory.h"

namespace Visualization
{

    struct CPainterFactory final : IPainterFactory
    {
        CPainterFactory(QGraphicsView*);
        PainterPtr createBruteForcePainter() const override;
        PainterPtr createAutomatonPainter() const override;

    private:

        QGraphicsView* m_view;

    };

} //Visualization
