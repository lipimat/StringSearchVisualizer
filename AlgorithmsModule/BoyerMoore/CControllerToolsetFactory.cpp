#include "CControllerToolsetFactory.h"
#include "CStepsExecutor.h"
#include "IPainter.h"

namespace Algorithms
{
namespace BoyerMoore
{

    template<class Painter>
    std::string_view CControllerToolsetFactory<Painter>::createName() const
    {
        return BOYER_MOORE_NAME;
    }

    template<class Painter>
    std::string_view CControllerToolsetFactory<Painter>::createInfo() const
    {
        return BOYER_MOORE_INFO;
    }

    template<class Painter>
    StepsExecutorPtr<Painter> CControllerToolsetFactory<Painter>::createStepsExecutor() const
    {
        return std::make_unique<CStepsExecutor<Painter>>();
    }

    template class CControllerToolsetFactory<Visualization::BoyerMoore::PainterPtr>;

} // BoyerMoore
} // Algorithms
