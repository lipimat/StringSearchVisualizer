#include "CControllerCreator.h"
#include "CControllerToolsetFactory.h"
#include "IPainter.h"
#include "../CController.h"
#include "../IPainterFactory.h"

namespace
{
using AutomatonPainter = Visualization::Automaton::PainterPtr;
using AutomatonToolsetFactory = Algorithms::Automaton::CControllerToolsetFactory<AutomatonPainter>;
using AutomatonController = Algorithms::CController<AutomatonPainter>;
}

namespace Algorithms
{
namespace Automaton
{
    ControllerPtr CControllerCreator::createController(const Visualization::PainterFactoryPtr& painterFactory) const
    {
        return std::make_unique<AutomatonController>(std::make_unique<AutomatonToolsetFactory>(), painterFactory->createAutomatonPainter());
    };

} // Automaton
} // Algorithms
