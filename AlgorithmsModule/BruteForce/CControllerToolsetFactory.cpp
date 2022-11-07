#include "CControllerToolsetFactory.h"
#include "CVisualizationPainter.h"

namespace Algorithms
{
namespace BruteForce
{

    std::string_view CControllerToolsetFactory::createName() const
    {
        return BRUTE_FORCE_NAME;
    }

    std::string_view CControllerToolsetFactory::createInfo() const
    {
        return BRUTE_FORCE_INFO;
    }

    AVisualizationPainter* CControllerToolsetFactory::createPainter(Window::IVisualizationWidget* device) const
    {
        return std::make_unique<CVisualizationPainter>(device).release();
    }

} //BruteForce
} //Algorithms
