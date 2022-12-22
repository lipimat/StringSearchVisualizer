#include "CControllerToolsetFactory.h"
#include "CStepsExecutor.h"
#include "IPainter.h"

namespace Algorithms
{
namespace BruteForce
{

    template<class Painter>
    std::string_view CControllerToolsetFactory<Painter>::createName() const
    {
        return BRUTE_FORCE_NAME;
    }

    template<class Painter>
    std::string_view CControllerToolsetFactory<Painter>::createInfo() const
    {
        return BRUTE_FORCE_INFO;
    }

    template<class Painter>
    StepsExecutorPtr<Painter> CControllerToolsetFactory<Painter>::createStepsExecutor() const
    {
        return std::make_unique<CStepsExecutor<Painter>>();
    }

    template class CControllerToolsetFactory<Visualization::BruteForce::PainterPtr>;

} // BruteForce
} // Algorithms
