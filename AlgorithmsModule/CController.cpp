#include "CController.h"

namespace Algorithms
{

    CController::CController(const IControllerToolsetFactory* const factory, Window::IVisualizationWidget* device) :
        m_algorithmInfo(factory->createInfo()), m_algorithmName(factory->createName()),
        m_painter(factory->createPainter(device)), m_widget(device)
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

    void CController::initializeVisualization() const
    {
        m_widget->updateWithGivenFunction([this]() { return m_painter->initializeVisualization(); });
    }

} //Algorithms
