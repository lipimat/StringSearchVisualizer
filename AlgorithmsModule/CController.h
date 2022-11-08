#pragma once

#include <string>

#include "IController.h"
#include "IControllerToolsetFactory.h"
#include "IVisualizationPainter.h"

namespace Algorithms
{

    using VisualizationPainterPtr = Window::Visualization::VisualizationPainterPtr;

    class CController final : public IController
    {
    public:

        CController(const ControllerToolsetFactoryPtr&, const VisualizationPainterPtr&);
        const std::string& getAlgorithmName() const override;
        const std::string& getAlgorithmInfo() const override;
        void initializeScene(const TextsPair&) const override;
        void cleanScene() const override;

    private:

        std::string m_algorithmName;
        std::string m_algorithmInfo;

        VisualizationPainterPtr m_painter;
    };

} //Algorithms
