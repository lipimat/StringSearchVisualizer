#pragma once

#include <string>

#include "IController.h"
#include "IControllerToolsetFactory.h"
#include "AVisualizationPainter.h"
#include "IVisualizationWidget.h"

namespace Algorithms
{

    class CController final : public IController
    {
    public:

        CController(const IControllerToolsetFactory* const, Window::IVisualizationWidget*);
        const std::string& getAlgorithmName() const override;
        const std::string& getAlgorithmInfo() const override;
        void initializeVisualization() const override;

    private:

        std::string m_algorithmName;
        std::string m_algorithmInfo;
        AVisualizationPainter* m_painter;
        Window::IVisualizationWidget* m_widget;
    };

} //Algorithms
