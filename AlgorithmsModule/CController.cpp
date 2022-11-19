#include "assert.h"

#include "CController.h"

#include "Steps/Constants.h"

namespace Algorithms
{
    class CController::Impl
    {
    public:

        explicit Impl(const ControllerToolsetFactoryPtr&, const Visualization::PainterFactoryPtr&);
        inline const std::string& getAlgorithmName() const { return m_algorithmName; };
        inline const std::string& getAlgorithmInfo() const { return m_algorithmInfo; };
        inline const Visualization::PainterPtr& getPainter() const { return m_painter; };
        inline const StepsExecutorPtr& getExecutor() const { return m_executor; };
        ~Impl() = default;

    private:
        const std::string m_algorithmName;
        const std::string m_algorithmInfo;

        const PainterPtr m_painter;
        const StepsExecutorPtr m_executor;
    };

    CController::Impl::Impl(
            const ControllerToolsetFactoryPtr& toolsetFactoryPtr,
            const Visualization::PainterFactoryPtr& painterFactoryPtr) :
        m_algorithmInfo(toolsetFactoryPtr->createInfo()),
        m_algorithmName(toolsetFactoryPtr->createName()),
        m_painter(toolsetFactoryPtr->createPainter(painterFactoryPtr)),
        m_executor(toolsetFactoryPtr->createStepsExecutor())
    {
        assert(m_painter != nullptr);
        assert(m_executor != nullptr);
    }

    CController::CController(const ControllerToolsetFactoryPtr& toolsetFactoryPtr,
                             const Visualization::PainterFactoryPtr& painterFactoryPtr) :
        m_impl(std::make_unique<CController::Impl>(toolsetFactoryPtr, painterFactoryPtr))
    {
        assert(m_impl != nullptr);
    }

    const std::string& CController::getAlgorithmName() const
    {
        return m_impl->getAlgorithmName();
    }

    const std::string& CController::getAlgorithmInfo() const
    {
        return m_impl->getAlgorithmInfo();
    }

    void CController::initializeScene(const TextsPair& userTexts) const
    {
        const auto& painter = m_impl->getPainter();
        const auto& stepsExecutor = m_impl->getExecutor();
        painter->drawBasicScene(userTexts);
        stepsExecutor->initialize(userTexts);
    }

    void CController::cleanScene() const
    {
        const auto& painter = m_impl->getPainter();
        painter->cleanWholeScene();
    }

    bool CController::nextStep() const
    {
        const auto& stepsExecutor = m_impl->getExecutor();
        const auto isAlgorithmInProgress = stepsExecutor->calculateNextStep() == Steps::EAlgorithmState::CONTINUE;
        if(isAlgorithmInProgress)
        {
            const auto& currentStep = stepsExecutor->getCurrentStep();
            assert(currentStep != nullptr);
            const auto& painter = m_impl->getPainter();
            currentStep->accept(painter);
        }
        return isAlgorithmInProgress;
    }

    CController::~CController() = default;

} //Algorithms
