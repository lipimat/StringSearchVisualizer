#include "assert.h"

#include "CController.h"

#include "Steps/Constants.h"

namespace Algorithms
{

    CController::CController(const ControllerToolsetFactoryPtr& factoryPtr,
                             const Visualization::PainterFactoryPtr& painterFactoryPtr) :
        m_algorithmInfo(factoryPtr->createInfo()), m_algorithmName(factoryPtr->createName()),
        m_painter(factoryPtr->createPainter(painterFactoryPtr)), m_executor(factoryPtr->createStepsExecutor())
    {
       assert(m_painter);
       assert(m_executor);
    }

    const std::string& CController::getAlgorithmName() const
    {
        return m_algorithmName;
    }

    const std::string& CController::getAlgorithmInfo() const
    {
        return m_algorithmInfo;
    }

    void CController::initializeScene(const TextsPair& userTexts) const
    {
        m_painter->drawBasicScene(userTexts);
        m_executor->initialize(userTexts);
    }

    void CController::cleanScene() const
    {
        m_painter->cleanWholeScene();
    }

    bool CController::nextStep() const
    {
        const auto isAlgorithmInProgress = m_executor->calculateNextStep() == Steps::EState::CONTINUE;
        if(isAlgorithmInProgress)
        {
            const auto& currentStep = m_executor->getCurrentStep();
            currentStep->accept(m_painter);
        }
        return isAlgorithmInProgress;
    }

} //Algorithms
