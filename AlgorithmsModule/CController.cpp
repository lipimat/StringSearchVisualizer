#include "CController.h"

namespace Algorithms
{

    CController::CController(const IControllerToolsetFactory* const factory) :
        m_algorithmInfo(factory->createInfo()), m_algorithmName(factory->createName())
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

} //Algorithms
