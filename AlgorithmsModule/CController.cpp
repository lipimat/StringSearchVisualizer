#include "CController.h"

namespace Algorithms
{

    CController::CController(const ControllerToolsetFactoryPtr& factoryPtr, const VisualizationPainterPtr& painterPtr) :
        m_algorithmInfo(factoryPtr->createInfo()), m_algorithmName(factoryPtr->createName()), m_painter(painterPtr)
    {
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
    }

    void CController::cleanScene() const
    {
        m_painter->cleanWholeScene();
    }

} //Algorithms
