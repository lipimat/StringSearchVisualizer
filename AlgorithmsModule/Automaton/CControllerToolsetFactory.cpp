#include "CControllerToolsetFactory.h"
#include "CStepsExecutor.h"
#include "IPainter.h"

namespace Algorithms
{
namespace Automaton
{

    template<class Painter>
    std::string_view CControllerToolsetFactory<Painter>::createName() const
    {
        return AUTOMATON_NAME;
    }

    template<class Painter>
    std::string_view CControllerToolsetFactory<Painter>::createInfo() const
    {
        return AUTOMATON_INFO;
    }

    template<class Painter>
    StepsExecutorPtr<Painter> CControllerToolsetFactory<Painter>::createStepsExecutor() const
    {
        return std::make_unique<CStepsExecutor<Painter>>();
    }

    template class CControllerToolsetFactory<Visualization::Automaton::PainterPtr>;

} // Automaton
} // Algorithms
