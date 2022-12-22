#pragma once

#include "IController.h"
#include "IStepsExecutor.h"
#include "IControllerToolsetFactory.h"

namespace Algorithms
{

    template<class Painter>
    class CController final : public IController
    {
    public:
        explicit CController(const ControllerToolsetFactoryPtr<Painter>&, Painter&&);
        const std::string& getAlgorithmName() const override;
        const std::string& getAlgorithmInfo() const override;
        void initializeScene(const TextsPair&) const override;
        void cleanScene() const override;
        bool nextStep() const override;
        ~CController() override;

    private:
        template<class PainterImpl>
        class Impl;
        std::unique_ptr<Impl<Painter>> m_impl;
    };

} // Algorithms
