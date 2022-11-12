#include "assert.h"

#include "CController.h"

#include "Steps/Constants.h"

namespace Algorithms
{

    CController::CController(const ControllerToolsetFactoryPtr& factoryPtr, const PainterPtr& painterPtr) :
        m_algorithmInfo(factoryPtr->createInfo()), m_algorithmName(factoryPtr->createName()),
        m_painter(painterPtr), m_executor(factoryPtr->createStepsExecutor())
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
        auto returnValue = true;
        if(m_executor->calculateNextStep() == Steps::EState::FINISHED)
            returnValue = false;
        return returnValue;
    }

} //Algorithms
