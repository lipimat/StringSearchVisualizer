#pragma once

#include <string>

#include "IController.h"
#include "IControllerToolsetFactory.h"
#include "IPainter.h"

namespace Algorithms
{

    using PainterPtr = Window::Visualization::PainterPtr;

    class CController final : public IController
    {
    public:

        explicit CController(const ControllerToolsetFactoryPtr&, const PainterPtr&);
        const std::string& getAlgorithmName() const override;
        const std::string& getAlgorithmInfo() const override;
        void initializeScene(const TextsPair&) const override;
        void cleanScene() const override;

    private:

        std::string m_algorithmName;
        std::string m_algorithmInfo;

        PainterPtr m_painter;
    };

} //Algorithms
