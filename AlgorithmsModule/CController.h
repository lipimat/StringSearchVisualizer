#pragma once

#include "IController.h"
#include "IControllerToolsetFactory.h"
#include "IPainterFactory.h"
#include "IStepsExecutor.h"

namespace Algorithms
{

    using PainterPtr = Visualization::PainterPtr;

    class CController final : public IController
    {
    public:

        explicit CController(const ControllerToolsetFactoryPtr&, const Visualization::PainterFactoryPtr&);
        const std::string& getAlgorithmName() const override;
        const std::string& getAlgorithmInfo() const override;
        void initializeScene(const TextsPair&) const override;
        void cleanScene() const override;
        bool nextStep() const override;
        ~CController();

    private:
        class Impl;
        std::unique_ptr<Impl> m_impl;
    };

} //Algorithms
