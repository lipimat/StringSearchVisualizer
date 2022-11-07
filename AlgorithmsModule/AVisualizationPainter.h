#pragma once

#include <QPainter>
#include "IVisualizationWidget.h"

namespace Algorithms
{

    class AVisualizationPainter : public QPainter
    {
    public:

        explicit AVisualizationPainter(Window::IVisualizationWidget *);

        virtual void initializeVisualization();

        virtual ~AVisualizationPainter() = default;
    };

} //Algorithms
